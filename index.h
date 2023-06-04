const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>Weather Reporting System by SASMA</title>
</head>
<style>
@import url(https://fonts.googleapis.com/css?family=Montserrat);
@import url(https://fonts.googleapis.com/css?family=Advent+Pro:400,200);

* {
  margin: 0;
  padding: 0;
}

body {
  height: 100vh;
  background: #ddffbc;
  font-family: Montserrat, Arial, sans-serif;
  display: flex;
  align-items: center;
}

h2 {
  font-size: 14px;
}

.widget {
  box-shadow: 0 40px 10px 5px rgba(0, 0, 0, 0.4);
  margin: 100px auto;
  height: 330px;
  position: relative;
  width: 500px;
}

.upper {
  border-radius: 5px 5px 0 0;
  background: #feffde;
  height: 200px;
  padding: 20px;
}

a:link {
  color: #52734d;
  font-size: 16px;
  font-weight: bold;
}

.date {
  font-size: 40px;
}

.year {
  font-size: 30px;
  color: #c1c1c1;
}

.place {
  color: #222;
  font-size: 40px;
}

.lower {
  background: #52734d;
  border-radius: 0 0 5px 5px;
  font-family: "Advent Pro";
  font-weight: 200;
  height: 130px;
  width: 100%;
}

.lower h2 {
  color: #feffde;
  font-size: 16px;
  margin-top: 10px;
}

.lower span {
  color: #feffde;
}

.clock {
  background: #52734d;
  border-radius: 100%;
  box-shadow: 0 0 0 15px #feffde, 0 10px 10px 5px rgba(0, 0, 0, 0.3);
  height: 150px;
  position: absolute;
  right: 25px;
  top: -35px;
  width: 150px;
}

.hour {
  background: #feffde;
  height: 50px;
  left: 50%;
  position: absolute;
  top: 25px;
  width: 4px;
}

.min {
  background: #feffde;
  height: 65px;
  left: 50%;
  position: absolute;
  top: 10px;
  transform: rotate(100deg);
  width: 4px;
}

.min,
.hour {
  border-radius: 5px;
  transform-origin: bottom center;
  transition: all 0.5s linear;
}

.infos {
  list-style: none;
}

.info {
  color: #fff;
  float: left;
  height: 100%;
  padding-top: 10px;
  text-align: center;
  width: 20%;
}

.info span {
  display: inline-block;
  font-size: 30px;
  margin-top: 25px;
}

.weather p {
  font-size: 20px;
  padding: 10px 0;
}

.anim {
  animation: fade 0.8s linear;
}

@keyframes fade {
  0% {
    opacity: 0;
  }

  100% {
    opacity: 1;
  }
}

a {
  text-align: center;
  text-decoration: none;
  font-size: 15px;
  font-weight: 500;
}
</style>
<body>
 
 
<div class="widget"> 
  <div class="clock">
    <div class="min" id="min"></div>
    <div class="hour" id="hour"></div>
  </div>
  <div class="upper">
    <div class="date" id="date">21 March</div>
    <div class="year">Temperature</div>
    <div class="place update" id="temperature">23 &deg;C</div>
  </div>
  <div style="text-align: center;"><a href="https://github.com/shivamaswal/weather_reporting_system" style="align:center">Weather Reporting System</a></div>
  <div class="lower">    
    <ul class="infos">
      <li class="info temp">
        <h2 class="title">TEMPERATURE</h2>
        <span class='update' id="temp">21 &deg;C</span>
      </li>
      <li class="info weather">
        <h2 class="title">PRESSURE</h2>
        <span class="update" id="pressure">0 mb</span>
      </li>
      <li class="info wind">
        <h2 class="title">RAIN</h2>
        <span class='update' id="rain">0%</span>
      </li>
      <li class="info humidity">
        <h2 class="title">HUMIDITY</h2>
        <span class='update' id="humidity">23%</span>
      </li>
      <li class="info altitude">
        <h2 class="title">ALTITUDE</h2>
        <span class='update' id="altitude">1000 m</span>
      </li>
    </ul>
  </div>
</div>
 
<script>
setInterval(drawClock, 2000);
    
function drawClock(){
    var now = new Date();
    var hour = now.getHours();
    var minute = now.getMinutes();
    var second = now.getSeconds();
    
    //Date
    var options = {year: 'numeric', month: 'long', day: 'numeric' };
    var today  = new Date();
    document.getElementById("date").innerHTML = today.toLocaleDateString("en-US", options);
    
    //hour
    var hourAngle = (360*(hour/12))+((360/12)*(minute/60));
    var minAngle = 360*(minute/60);
    document.getElementById("hour").style.transform = "rotate("+(hourAngle)+"deg)";
    //minute
    document.getElementById("min").style.transform = "rotate("+(minAngle)+"deg)";
 
    //Get Humidity Temperature and Rain Data
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
      var txt = this.responseText;
      var obj = JSON.parse(txt); //Ref: https://www.w3schools.com/js/js_json_parse.asp
        console.log(obj);
         document.getElementById("rain").innerHTML = obj.Rain + "%";
        document.getElementById("temperature").innerHTML = Math.round(obj.Temperature) + "&deg;C";
        document.getElementById("temp").innerHTML = Math.round(obj.Temperature) + "&deg;C";
        document.getElementById("humidity").innerHTML = Math.round(obj.Humidity) + "%";
        document.getElementById("pressure").innerHTML = Math.round((obj.Pressure/100)) + " mb";
        document.getElementById("altitude").innerHTML = Math.round(obj.Altitude) + " m";


      }  
    };
   xhttp.open("GET", "readADC", true); //Handle readADC server on ESP8266
   xhttp.send();
}
</script>
</body>
</html>
)=====";
