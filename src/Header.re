[@bs.module] external logo : string = "./logo.svg";

let component = ReasonReact.statelessComponent("Header");

let make = (~heading: string, _children) => {
  ...component,
  render: _self =>
    <div className="App-header">
      <img src=logo className="App-logo" alt="logo" />
      <h1> (ReasonReact.stringToElement(heading)) </h1>
    </div>
};