open Webapi;

type property =
  | Id(string)
  | TextContent(string);

type vNode =
  | DomNode(string, list(property), list(vNode))
  | Component;

let applyProp = (elm: Dom.Element.t, property: property) =>
  switch property {
  | Id(id) => Dom.Element.setId(elm, id)
  | TextContent(text) => Dom.Element.setTextContent(elm, text)
  };

let reify = (vNode: vNode, domNode: Dom.Element.t) =>
  switch vNode {
  | Component => ()
  | DomNode(tag, props, children) =>
    let elm = Dom.Document.createElement(tag, Dom.document);
    Belt.List.forEach(props, applyProp(elm));
    let parent = Dom.Element.parentNode(domNode);
    switch parent {
    | None => failwith("NoParent") |> ignore
    | Some(parent) =>
      Dom.Node.insertBefore(elm, domNode, parent) |> ignore;
      Dom.Node.removeChild(domNode, parent) |> ignore;
    };
    ();
  };