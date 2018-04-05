open Webapi;

type property =
  | Id(string);

type vNode =
  | HTML(string, list(property), list(vNode))
  | Text(string)
  | Component(vNode);

let applyProp = (element, property) =>
  switch property {
  | Id(id) => Dom.Element.setId(element, id)
  };

let rec reify = (vNode) =>
switch vNode {
| Component(innerVNode) => reify(innerVNode)
| HTML(tag, props, children) =>
let element = Dom.Document.createElement(tag, Dom.document);
    Belt.List.forEach(props, applyProp(element));
    Belt.List.forEach(children, (child) => switch child {
      | Text(content) => Dom.Document.createTextNode(content, Dom.document) |> Dom.Element.appendChild(_, element)
      | _ => reify(child) |> Dom.Element.appendChild(_, element)
      });
    element;
  | Text(content) =>
    let element = reify(HTML("div", [], []));
    Dom.Element.setTextContent(element, content);
    element;
  };

let mount = (node, target) => {
  let parent = Dom.Element.parentElement(target);
  switch parent {
  | None => failwith("NoParent") |> ignore
  | Some(parent) =>
    Dom.Element.appendChild(node, parent) |> ignore;
    Dom.Element.removeChild(target, parent) |> ignore;
  };
};