// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

import * as React       from "react";
import * as SadPng      from "./sad.png";
import * as ShrugPng    from "./shrug.png";
import * as ReasonReact from "reason-react/src/ReasonReact.js";
import * as AwesomePng  from "./awesome.png";
import * as LoadingGif  from "./loading.gif";

var component = ReasonReact.statelessComponent("Answer");

function make(data, _) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function () {
      var match = data[/* responseType */2];
      var image;
      switch (match) {
        case "Affirmative" : 
            image = AwesomePng;
            break;
        case "Contrary" : 
            image = SadPng;
            break;
        case "Neutral" : 
            image = ShrugPng;
            break;
        default:
          image = LoadingGif;
      }
      return React.createElement("div", {
                  className: "answerContainer"
                }, React.createElement("img", {
                      className: "resultReaction",
                      src: image,
                      width: "130px"
                    }), React.createElement("div", {
                      className: "resultText"
                    }, data[/* answer */1]));
    });
  return newrecord;
}

export {
  component ,
  make      ,
  
}
/* component Not a pure module */
