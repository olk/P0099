// Represent a subset of interesting SAX events
struct BaseEvent{
   BaseEvent(const BaseEvent&)=delete;
   BaseEvent& operator=(const BaseEvent&)=delete;
   virtual ~BaseEvent() {}
   virtual std::ostream& stream(std::ostream&) const=0;
};

std::ostream& operator<<(std::ostream& out,const BaseEvent& event)
{ return event.stream(out); }

// End of document or element
struct CloseEvent: public BaseEvent{
   // CloseEvent binds (without copying) the TagType reference.
   CloseEvent(const xml::sax::Parser::TagType& name):
       mName(name)
   {}

   virtual std::ostream& stream(std::ostream& out) const
   { return out<<"CloseEvent('"<<mName<<"')\n"; }

   const xml::sax::Parser::TagType& mName;
};

// Start of document or element
struct OpenEvent: public CloseEvent{
   // In addition to CloseEvent's TagType, OpenEvent binds AttributeIterator.
   OpenEvent(const xml::sax::Parser::TagType& name,
             xml::sax::AttributeIterator& attrs):
       CloseEvent(name),
       mAttrs(attrs)
   {}

   virtual std::ostream& stream(std::ostream& out) const{
       out<<"OpenEvent('"<<mName<<"'";
       xml::sax::AttributeIterator::OptionalAttribute attribute;
       while ((attribute=mAttrs.getNext())){
           out<<", '"<< attribute->name<<"'='"<<attribute->value<<"'";
       }
       return out<<")\n";
   }

   xml::sax::AttributeIterator& mAttrs;
};

// text within an element
struct TextEvent: public BaseEvent{
   // TextEvent binds the CharIterator.
   TextEvent(xml::sax::CharIterator& text):
       mText(text)
   {}

   virtual std::ostream& stream(std::ostream& out) const
   { return out<<"TextEvent('"<<mText.getText()<<"')\n"; }

   xml::sax::CharIterator& mText;
};

// The parsing coroutine instantiates BaseEvent subclass instances and
// successively shows them to the main program. It passes a reference so we
// don't slice the BaseEvent subclass.
typedef std::asymmetric_coroutine<const BaseEvent&> coro_t;

void parser(coro_t::push_type& sink,std::istream& in){
   xml::sax::Parser xparser;
   // startDocument() will send OpenEvent
   xparser.startDocument([&sink](const xml::sax::Parser::TagType& name,
                                 xml::sax::AttributeIterator& attrs)
                         {
                             sink(OpenEvent(name,attrs));
                         });
   // startTag() will likewise send OpenEvent
   xparser.startTag([&sink](const xml::sax::Parser::TagType& name,
                            xml::sax::AttributeIterator& attrs)
                    {
                        sink(OpenEvent(name,attrs));
                    });
   // endTag() will send CloseEvent
   xparser.endTag([&sink](const xml::sax::Parser::TagType& name)
                  {
                      sink(CloseEvent(name));
                  });
   // endDocument() will likewise send CloseEvent
   xparser.endDocument([&sink](const xml::sax::Parser::TagType& name)
                       {
                           sink(CloseEvent(name));
                       });
   // characters() will send TextEvent
   xparser.characters([&sink](xml::sax::CharIterator& text)
                      {
                          sink(TextEvent(text));
                      });
   // parse the document, firing all the above
   xparser.parse(in);
}

const CloseEvent& process(coro_t::pull_type& events,const OpenEvent& context,
                          const std::string& indent=""){
   xml::sax::Parser::TagType tagName = context.mName;
   // Each time we're called, we've just retrieved 'context' from 'events' --
   // so the first thing we have to do is pass control to 'events' to let it
   // deliver the next event. Of course, each time we come back we must
   // check for the end of the results stream.
   while(events(),events){
       const BaseEvent& event=events.get();
       // std::cout << event;
       const OpenEvent* oe;
       const CloseEvent* ce;
       const TextEvent* te;
       if((oe=dynamic_cast<const OpenEvent*>(&event))){
           process(events,*oe,indent+"    ");
       }
       else if((ce=dynamic_cast<const CloseEvent*>(&event))){
           assert(ce->mName == tagName);
           return *ce;
       }
       else if((te=dynamic_cast<const TextEvent*>(&event))){
           std::cout<<indent<<"'"<<te->mText.getText()<<"'\n";
       }
   }
}

// stream XML-document
std::istringstream in(doc);
coro_t::pull_type events(boost::bind(parser,_1,boost::ref(in)));
// We fully expect at least ONE event.
assert(events);
// This dynamic_cast<&> is itself an assertion that the first event is an
// OpenEvent.
const OpenEvent& context=dynamic_cast<const OpenEvent&>(events.get());
process(events, context);
