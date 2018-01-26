// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

import * as React       from "react";
import * as LogoSvg     from "./logo.svg";
import * as ReasonReact from "reason-react/src/ReasonReact.js";

var component = ReasonReact.statelessComponent("Header");

function make(heading, _) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function () {
      return React.createElement("div", {
                  className: "App-header"
                }, React.createElement("img", {
                      className: "App-logo",
                      alt: "logo",
                      src: LogoSvg
                    }), React.createElement("h1", undefined, heading));
    });
  return newrecord;
}

export {
  component ,
  make      ,
  
}
/* component Not a pure module */