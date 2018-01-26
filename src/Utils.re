[@bs.val] external encodeURIComponent : string => string = "";

let baseURL = "https://8ball.delegator.com/magic/JSON/";

let makeURL = params => baseURL ++ encodeURIComponent(params);

let truncateString = num =>
  string_of_float(
    float_of_int(truncate(float_of_string(num) *. 100.0)) /. 100.0
  );

let ensureTwoDecimalPlaces = num => {
  let result = truncateString(num);
  let length = result |> String.length;
  switch length {
  | 5 => truncateString(num) ++ "0"
  | _ => truncateString(num)
  };
};