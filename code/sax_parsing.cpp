// Represent a subset of interesting SAX events
struct BaseEvent{
   BaseEvent(const BaseEvent&)=delete;
   BaseEvent& operator=(const BaseEvent&)=delete;
};

// End of document or element
struct CloseEvent: public BaseEvent{
   // CloseEvent binds (without copying) the TagType reference.
   CloseEvent(const xml::sax::Parser::TagType& name):
       mName(name)
   {}

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

   xml::sax::AttributeIterator& mAttrs;
};

// text within an element
struct TextEvent: public BaseEvent{
   // TextEvent binds the CharIterator.
   TextEvent(xml::sax::CharIterator& text):
       mText(text)
   {}

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
   try
   {
       // parse the document, firing all the above
       xparser.parse(in);
   }
   catch (xml::Exception e)
   {
       // xml::sax::Parser throws xml::Exception. Helpfully translate the
       // name and provide it as the what() string.
       throw std::runtime_error(exception_name(e));
   }
}

// Recursively traverse the incoming XML document on the fly, pulling
// BaseEvent& references from 'events'.
// 'indent' illustrates the level of recursion.
// Each time we're called, we've just retrieved an OpenEvent from 'events';
// accept that as a param.
// Return the CloseEvent that ends this element.
const CloseEvent& process(coro_t::pull_type& events,const OpenEvent& context,
                          const std::string& indent=""){
   // Capture OpenEvent's tag name: as soon as we advance the parser, the
   // TagType& reference bound in this OpenEvent will be invalidated.
   xml::sax::Parser::TagType tagName = context.mName;
   // Since the OpenEvent is still the current value from 'events', pass
   // control back to 'events' until the next event. Of course, each time we
   // come back we must check for the end of the results stream.
   while(events()){
       // Another event is pending; retrieve it.
       const BaseEvent& event=events.get();
       const OpenEvent* oe;
       const CloseEvent* ce;
       const TextEvent* te;
       if((oe=dynamic_cast<const OpenEvent*>(&event))){
           // When we see OpenEvent, recursively process it.
           process(events,*oe,indent+"    ");
       }
       else if((ce=dynamic_cast<const CloseEvent*>(&event))){
           // When we see CloseEvent, validate its tag name and then return
           // it. (This assert is really a check on xml::sax::Parser, since
           // it already validates matching open/close tags.)
           assert(ce->mName == tagName);
           return *ce;
       }
       else if((te=dynamic_cast<const TextEvent*>(&event))){
           // When we see TextEvent, just report its text, along with
           // indentation indicating recursion level.
           std::cout<<indent<<"text: '"<<te->mText.getText()<<"'\n";
       }
   }
}

// pretend we have an XML file of arbitrary size
std::istringstream in(doc);
try
{
   coro_t::pull_type events(std::bind(parser,_1,std::ref(in)));
   // We fully expect at least ONE event.
   assert(events);
   // This dynamic_cast<&> is itself an assertion that the first event is an
   // OpenEvent.
   const OpenEvent& context=dynamic_cast<const OpenEvent&>(events.get());
   process(events, context);
}
catch (std::exception& e)
{
   std::cout << "Parsing error: " << e.what() << '\n';
}
