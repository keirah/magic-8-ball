type buttonHW = {
  height: int,
  width: int
};

type state = {
  responseData: option(MagicEightBall.responseData),
  counter: int,
  fetching: bool,
  buttonRef: ref(option(ReasonReact.reactRef)),
  wrapperRef: ref(option(Dom.element)),
  buttonAttributes: option(buttonHW)
};

let setButtonRef = (r, {ReasonReact.state}) =>
  state.buttonRef := Js.Nullable.to_opt(r);

let setWrapperRef = (r, {ReasonReact.state}) =>
  state.wrapperRef := Js.Nullable.to_opt(r);

/* wondering about Js.Nullable.to_opt? See the note below */
type action =
  | Click
  | LoadData(MagicEightBall.responseData)
  | SetButtonAttributes(buttonHW)
  | FetchData;

let component = ReasonReact.reducerComponent("App");

[%bs.raw "require('./app.scss')"];

[@bs.module] external loading : string = "./loading.gif";

let make = _children => {
  ...component,
  initialState: () => (
    {
      responseData: None,
      counter: 0,
      fetching: false,
      buttonRef: ref(None),
      wrapperRef: ref(None),
      buttonAttributes: None
    }: state
  ),
  reducer: (action, state) =>
    switch action {
    | LoadData((responseData: MagicEightBall.responseData)) =>
      ReasonReact.Update({
        ...state,
        fetching: false,
        responseData: Some(responseData)
      })
    | FetchData =>
      ReasonReact.UpdateWithSideEffects(
        {...state, fetching: true},
        (
          self =>
            MagicEightBall.fetchAnswer(
              Utils.makeURL(
                List.nth(
                  QuestionData.questions,
                  state.counter mod List.length(QuestionData.questions)
                )
              )
            )
            |> Js.Promise.then_(responseData => {
                 (self.reduce((_) => LoadData(responseData)))(responseData);
                 Js.Promise.resolve();
               })
            |> Js.Promise.catch(error => Js.Promise.resolve(Js.log(error)))
            |> ignore
        )
      )
    | SetButtonAttributes(button) =>
      ReasonReact.Update({...state, buttonAttributes: Some(button)})
    | Click =>
      ReasonReact.UpdateWithSideEffects(
        {...state, counter: state.counter + 1, responseData: None},
        (self => self.send(FetchData))
      )
    },
  didMount: self => {
    switch self.state.wrapperRef^ {
    | None => ()
    | Some(domRef) =>
      let domObj = domRef |> ReactDOMRe.domElementToObj;
      let rect = domObj##getBoundingClientRect();
      self.send(
        SetButtonAttributes(
          {height: rect##height, width: rect##width}: buttonHW
        )
      );
      self.send(FetchData);
    };
    ReasonReact.NoUpdate;
  },
  didUpdate: ({oldSelf, newSelf}) =>
    switch (oldSelf.state.buttonAttributes, newSelf.state.wrapperRef^) {
    | (None, None) => ()
    | (Some(_domRef), None) => ()
    | (Some(oldButtonAttributes), Some(domRef)) =>
      let domObj = domRef |> ReactDOMRe.domElementToObj;
      let rect = domObj##getBoundingClientRect();
      if (oldButtonAttributes.width !== rect##width) {
        newSelf.send(
          SetButtonAttributes(
            {height: rect##height, width: rect##width}: buttonHW
          )
        );
      };
    | (None, Some(domRef)) =>
      let domObj = domRef |> ReactDOMRe.domElementToObj;
      let rect = domObj##getBoundingClientRect();
      newSelf.send(
        SetButtonAttributes(
          {height: rect##height, width: rect##width}: buttonHW
        )
      );
    },
  render: ({state, handle, send}) => {
    let answer =
      switch (state.responseData: option(MagicEightBall.responseData)) {
      | Some(responseData) => <Answer data=responseData />
      | None => <div className="noData"> <img src=loading width="200" /> </div>
      };
    let buttonDetails =
      switch (state.buttonAttributes: option(buttonHW)) {
      | Some(buttonAttributes) =>
        let width = string_of_int(buttonAttributes.width);
        <div>
          (
            ReasonReact.stringToElement(
              "(" ++ Utils.ensureTwoDecimalPlaces(width) ++ "px)"
            )
          )
        </div>;
      | None =>
        <div className="noData">
          (ReasonReact.stringToElement("No data"))
        </div>
      };
    <div className="app">
      <div className="appContainer">
        <Header
          heading=(
            "Rick Astley's Magic 8 Ball: " ++ string_of_int(state.counter: int)
          )
        />
        <Arrow />
        <div className="buttonDetails"> buttonDetails </div>
        <div className="buttonWrapper" ref=(handle(setWrapperRef))>
          <ButtonWrapper
            ref=(handle(setButtonRef))
            handleButtonClick=(_event => send(Click))
            label=(
              ReasonReact.stringToElement(
                List.nth(
                  QuestionData.questions,
                  state.counter mod List.length(QuestionData.questions)
                )
              )
            )
          />
        </div>
        <div className="result">
          <div className="resultImageContainer"> answer </div>
        </div>
      </div>
    </div>;
  }
};