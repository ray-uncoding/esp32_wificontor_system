#ifndef index
#define index

const char* index_html PROGMEM = R"HTMLHOMEPAGE(
<!DOCTYPE HTML>
<html>

<head>
    <title>ESP Web Server</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <style>
        html {
            font-family: Arial, Helvetica, sans-serif;
            text-align: center;
        }

        h1 {
            font-size: 1.8rem;
            color: white;
        }

        h2 {
            font-size: 1.5rem;
            font-weight: bold;
            color: #143642;
        }

        h3 {
            font-size: 0.8rem;
            font-weight: bold;
            color: #b3ced7;
        }

        .topnav {
            overflow: hidden;
            background-color: #143642;
        }

        body {
            margin: 0;
        }

        .content {
            padding: 30px;
            max-width: 600px;
            margin: 0 auto;
        }

        .card {
            background-color: #F8F7F9;
            ;
            box-shadow: 2px 2px 12px 1px rgba(140, 140, 140, .5);
            padding-top: 10px;
            padding-bottom: 300px;
        }

        .button {
            padding: 15px 50px;
            font-size: 24px;
            text-align: center;
            outline: none;
            color: #fff;
            background-color: #0f8b8d;
            border: none;
            border-radius: 5px;
            -webkit-touch-callout: none;
            -webkit-user-select: none;
            -khtml-user-select: none;
            -moz-user-select: none;
            -ms-user-select: none;
            user-select: none;
            -webkit-tap-highlight-color: rgba(0, 0, 0, 0);
        }

        .button:active {
            background-color: #0f8b8d;
            box-shadow: 2 2px #CDCDCD;
            transform: translateY(2px);
        }

        .state {
            font-size: 1.5rem;
            color: #8c8c8c;
            font-weight: bold;
        }

        .crosshair {
            display: inline-block;
            width: 24px;
            height: 24px;
            position: relative;
            border-radius: 100%;            
            border: 2px solid #d20f0f;            
            box-sizing: border-box;
        }

        .crosshair::before,
        .crosshair::after {
            content: "";
            position: absolute;
            background-color: #e31919;
        }

        .crosshair::before {
            left: 50%;
            transform: translateX(-50%);
            top: 0;
            width: 2px;
            height: 100%;
        }

        .crosshair::after {
            top: 50%;
            transform: translateY(-50%);
            left: 0;
            height: 2px;
            width: 100%;
        }
    </style>

    <title>ESP Web Server</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
</head>

<body>
    <div class="topnav">
        <h1> IRMP </h1>
        <h3> Intelligent Rescue Mobile Platform </h3>
    </div>
    <table id="mainTable" style="width:400px;margin:auto;table-layout:fixed" CELLSPACING=10>
        <tr>
            <img id="cameraImage" src="" style="width:400px;height:250px"></td>
        </tr>
        <tr>
            <td></td>
            <td class="button" ontouchstart='sendButtonInput("Move","1")' ontouchend='sendButtonInput("Move","0")'><span
                    class="arrows">&#8679;</span></td>
            <td></td>
        </tr>
        <tr>
            <td class="button" ontouchstart='sendButtonInput("Move","3")' ontouchend='sendButtonInput("Move","0")'><span
                    class="arrows">&#8678;</span></td>
            <td class="button" ontouchstart='sendButtonInput("Move","5")' ontouchend='sendButtonInput("Move","0")'>
                <span class="crosshair"></span>
            </td>
            <td class="button" ontouchstart='sendButtonInput("Move","4")' ontouchend='sendButtonInput("Move","0")'><span
                    class="arrows">&#8680;</span></td>
        </tr>
        <tr>
            <td></td>
            <td class="button" ontouchstart='sendButtonInput("Move","2")' ontouchend='sendButtonInput("Move","0")'><span
                    class="arrows">&#8681;</span></td>
            <td></td>
        </tr>
        <tr />
        <tr />
        <tr>
            <td style="text-align:left"><b>head:</b></td>
            <td colspan=2>
                <div class="slidecontainer">
                    <input type="range" min="0" max="255" value="125" class="slider" id="head"
                        oninput='sendButtonInput("head",value)'>
                </div>
            </td>
        </tr>
        <tr>
            <td style="text-align:left"><b>left front foot:</b></td>
            <td colspan=2>
                <div class="slidecontainer">
                    <input type="range" min="0" max="255" value="125" class="slider" id="left_front_foot"
                        oninput='sendButtonInput("left_front_foot",value)'>
                </div>
            </td>
        </tr>
        <tr>
            <td style="text-align:left"><b>Left hind foot:</b></td>
            <td colspan=2>
                <div class="slidecontainer">
                    <input type="range" min="0" max="255" value="125" class="slider" id="left_hind_foot"
                        oninput='sendButtonInput("left_hind_foot",value)'>
                </div>
            </td>
        </tr>
        <tr>
            <td style="text-align:left"><b>right front foot:</b></td>
            <td colspan=2>
                <div class="slidecontainer">
                    <input type="range" min="0" max="255" value="125" class="slider" id="right_front_foot"
                        oninput='sendButtonInput("right_front_foot",value)'>
                </div>
            </td>
        </tr>
        <tr>
            <td style="text-align:left"><b>right hind foot:</b></td>
            <td colspan=2>
                <div class="slidecontainer">
                    <input type="range" min="0" max="255" value="125" class="slider" id="right_hind_foot"
                        oninput='sendButtonInput("right_hind_foot",value)'>
                </div>
            </td>
        </tr>
    </table>

    <script>
        var webSocketCameraUrl = "ws:\/\/" + window.location.hostname + "/Camera";
        var webSocketCarInputUrl = "ws:\/\/" + window.location.hostname + "/CarInput";
        var websocketCamera;
        var websocketCarInput;

        function initCameraWebSocket() {
            websocketCamera = new WebSocket(webSocketCameraUrl);
            websocketCamera.binaryType = 'blob';
            websocketCamera.onopen = function (event) { };
            websocketCamera.onclose = function (event) { setTimeout(initCameraWebSocket, 2000); };
            websocketCamera.onmessage = function (event) {
                var imageId = document.getElementById("cameraImage");
                imageId.src = URL.createObjectURL(event.data);
            };
        }
        function initCarInputWebSocket() {
            websocketCarInput = new WebSocket(webSocketCarInputUrl);
            websocketCarInput.onopen = function (event) {
                sendButtonInput("left_front_foot", document.getElementById("left_front_foot").value);
                sendButtonInput("left_hind_foot", document.getElementById("left_hind_foot").value);
                sendButtonInput("right_front_foot", document.getElementById("right_front_foot").value);
                sendButtonInput("right_hind_foot", document.getElementById("right_hind_foot").value);
            };
            websocketCarInput.onclose = function (event) { setTimeout(initCarInputWebSocket, 2000); };
            websocketCarInput.onmessage = function (event) { };
        }

        function onLoad(event) {
            initCameraWebSocket();
            initCarInputWebSocket();
        }

        function sendButtonInput(key, value) {
            var data = key + "," + value;
            websocketCarInput.send(data);
        }

        window.onload = initWebSocket;
        document.getElementById("mainTable").addEventListener("touchend", function (event) {
            event.preventDefault()
        });

    </script>

</body>

</html>
)HTMLHOMEPAGE";

#endif