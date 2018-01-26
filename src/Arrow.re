let component = ReasonReact.statelessComponent("Arrow");

/* This section has been taken from the great code pen https://codepen.io/zomgbre/pen/kmCsp */
let make = _children => {
  ...component,
  render: _self =>
    <div className="things">
      <div className="content">
        <div className="arrow">
          <div className="curve" />
          <div className="point" />
        </div>
      </div>
    </div>
};