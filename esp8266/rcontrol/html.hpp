static const char HEADER[] = R"rawliteral(
<!DOCTYPE HTML>
<html>

  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Relay control</title>
    <meta http-equiv="refresh" content="60">
    <style>
      html,
      body,
      h1,
      h2,
      h3,
      p,
      div,
      span {
        margin: 0;
        padding: 0;
        border: 0;
        font-size: 100%;
        font: inherit;
        vertical-align: baseline;
      }

      body {
        font-family: sans-serif;
        line-height: 1;
        text-align: center;
        padding-top: 20px;
        font-size: 20px;
        margin: auto;
        min-width: 250px;
        max-width: 250px;
        background-color: #222;
        color: #aaa;
      }

      input {
        width: 50px;
        font-size: 20px;
        min-width: 150px;
        max-width: 150px;
      }

      form {
        padding-top: 8px;
      }

      h1 {
        font-size: 28px;
      }

      p:first-of-type {
        padding-top: 32px;
      }

      p {
        padding-top: 4px;
        padding-bottom: 4px;

      }

      .red {
        color: red;
      }

      .green {
        color: green;
      }

      .bgRedGreen {
        background-image: linear-gradient(to bottom, green 0%, red 100%);
      }

      .bgRed {
        background: red;
      }

      .bgGreen {
        background: green;
      }

    </style>
  </head>

  <body>
    <h1>Relay control</h1>
    <form action="/pulse" method="post">
      <input type="submit" value="Quick On/Off" class="bgRedGreen" />
    </form>
    <form action="/on" method="post">
      <input type="submit" value="Turn On" class="bgGreen" />
    </form>
    <form action="/off" method="post">
      <input type="submit" value="Turn Off" class="bgRed" />
    </form>

)rawliteral";

static const char FOOTER[] = R"rawliteral(
  </body>

</html>
)rawliteral";

static String uptime()
{
  char buf[15];

  unsigned long nowMillis = millis();
  unsigned long seconds = nowMillis / 1000;
  int days = seconds / 86400;
  seconds %= 86400;
  byte hours = seconds / 3600;
  seconds %= 3600;
  byte minutes = seconds / 60;
  seconds %= 60;
  snprintf(buf, sizeof(buf), "%d:%02d:%02d:%02d", days, hours, minutes, seconds);

  return String(buf);
}

String render(bool isRelayOn)
{
  String ret = "";

  ret += HEADER;
  if (isRelayOn)
  {
    ret += R"rawliteral(<p>Status: <strong class="green">On</strong></p>)rawliteral";
  }
  else
  {
    ret += R"rawliteral(<p>Status: <strong class="red">Off</strong></p>)rawliteral";
  }

  ret += "<p>Uptime: ";
  ret += uptime();
  ret += "</p>";

  ret += "<p>Free heap: ";
  ret += String(ESP.getFreeHeap());
  ret += "</p>";

  ret += FOOTER;

  return ret;
}
