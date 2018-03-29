open VNode;

open Webapi;

switch (Dom.Document.getElementById("root", Dom.document)) {
| None => ()
| Some(rootNode) =>
  reify(
    DomNode("div", [Id("demo"), TextContent("Hello, World!")], []),
    rootNode
  )
};