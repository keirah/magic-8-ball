let component = ReasonReact.statelessComponent("Answer");

[@bs.module] external awesome : string = "./awesome.png";

[@bs.module] external shrug : string = "./shrug.png";

[@bs.module] external sad : string = "./sad.png";

[@bs.module] external loading : string = "./loading.gif";

[@bs.module] external eightBall : string = "./Magic_eight_ball.png";

let make = (~data: MagicEightBall.responseData, _children) => {
  ...component,
  render: _self => {
    let image =
      switch data.responseType {
      | "Affirmative" => awesome
      | "Neutral" => shrug
      | "Contrary" => sad
      | _ => loading
      };
    <div className="answerContainer">
      <img className="resultReaction" src=image width="130px" />
      <div className="resultText">
        (ReasonReact.stringToElement(data.answer))
      </div>
    </div>;
  }
};