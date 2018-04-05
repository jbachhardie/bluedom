open VNode;

open Webapi;

switch (Dom.Document.getElementById("root", Dom.document)) {
| None => ()
| Some(rootNode) =>
  reify(Component(HTML("div", [Id("demo")], [Text("Hello, World!")]))) |> mount(rootNode)
};