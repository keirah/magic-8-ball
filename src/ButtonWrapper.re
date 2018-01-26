[@bs.module "./Button"] external buttonRe : ReasonReact.reactClass = "default";

let make = (~handleButtonClick, ~label, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=buttonRe,
    ~props={"label": label, "handleButtonClick": handleButtonClick},
    children
  );