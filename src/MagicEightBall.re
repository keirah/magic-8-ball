type responseData = {
  question: string,
  answer: string,
  responseType: string
};

let decodeResponseJson = json : responseData =>
  Json.Decode.{
    question: field("question", string, json),
    answer: field("answer", string, json),
    responseType: field("type", string, json)
  };

let parseResponseJson = json =>
  Json.Decode.(field("magic", decodeResponseJson, json));

let fetchAnswer = url =>
  Bs_fetch.fetch(url)
  |> Js.Promise.then_(Bs_fetch.Response.json)
  |> Js.Promise.then_(json => Js.Promise.resolve(parseResponseJson(json)));