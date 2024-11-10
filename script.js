var firebaseConfig = {
apiKey: "AIzaSyAn0rRvInY8z2XsOMulwNpv9ckU-OKB2CY",
authDomain: "smh-iot-2e746.firebaseapp.com",
databaseURL: "https://smh-iot-2e746-default-rtdb.firebaseio.com",
projectId: "smh-iot-2e746",
storageBucket: "smh-iot-2e746.appspot.com",
messagingSenderId: "639089713442",
appId: "1:639089713442:web:72bc80c666315b0e49057b",
measurementId: "G-GJYH1F0S3D"
};

firebase.initializeApp(firebaseConfig);
var database = firebase.database();

//SLIDER PUMP
// var sliderpump = document.getElementById("slider-water");
// sliderpump.oninput = function(){
//     var firebaseRef = firebase.database().ref().child("/IOT/pumpwater");
//     firebaseRef.set(sliderpump.value);     
// }
// //Status PUMP
// database.ref("/IOT/pumpwater").on("value", function(snap){      
//     sliderpump.value = snap.val();
// });

// Y1 - DOOR
// Y2 - LED 0

// Y3 - FAN 1
// Y4 - LED 1

// Y5 - FAN 2
// Y6 - LED 2

// X1 - DHT11 T
// X2 - DHT11 H
// X3 - MQ2
// X4 - IR


//Y1
var Y1 = 1;
var onbt1 = document.getElementById("act"+ Y1);
onbt1.onclick = function(){
    database.ref("/TEKYQ3/smh/I").update({
        Y1 : 1
    });
}
var offbt1 = document.getElementById("unact"+ Y1);
offbt1.onclick = function(){
    database.ref("/TEKYQ3/smh/I").update({
        Y1 : 0
    });
}

database.ref("/TEKYQ3/smh/I/Y1").on("value", function(snapshot){
    var ssled = snapshot.val();
    if(ssled==1){
        document.getElementById("unact" + Y1).style.display = "block";
		document.getElementById("act" + Y1).style.display = "none";
        document.getElementById("unst"+ Y1).style.display = "block";
		document.getElementById("ast"+ Y1).style.display = "none";
    }
    else{
        document.getElementById("unact"+ Y1).style.display = "none";
		document.getElementById("act"+ Y1).style.display = "block";
        document.getElementById("unst"+ Y1).style.display = "none";
		document.getElementById("ast"+ Y1).style.display = "block";
    }
})

//Y2
var Y2 = 2;
var onbt1 = document.getElementById("act"+ Y2);
onbt1.onclick = function(){
    database.ref("/TEKYQ3/smh/I").update({
        Y2 : 1
    });
}
var offbt1 = document.getElementById("unact"+ Y2);
offbt1.onclick = function(){
    database.ref("/TEKYQ3/smh/I").update({
        Y2 : 0
    });
}

database.ref("/TEKYQ3/smh/I/Y2").on("value", function(snapshot){
    var ssled = snapshot.val();
    if(ssled==1){
        document.getElementById("unact" + Y2).style.display = "block";
		document.getElementById("act" + Y2).style.display = "none";
        document.getElementById("unst"+ Y2).style.display = "block";
		document.getElementById("ast"+ Y2).style.display = "none";
    }
    else{
        document.getElementById("unact"+ Y2).style.display = "none";
		document.getElementById("act"+ Y2).style.display = "block";
        document.getElementById("unst"+ Y2).style.display = "none";
		document.getElementById("ast"+ Y2).style.display = "block";
    }
})

//Y3
var Y3 = 3;
var onbt1 = document.getElementById("act"+ Y3);
onbt1.onclick = function(){
    database.ref("/TEKYQ3/smh/I").update({
        Y3 : 1
    });
}
var offbt1 = document.getElementById("unact"+ Y3);
offbt1.onclick = function(){
    database.ref("/TEKYQ3/smh/I").update({
        Y3 : 0
    });
}

database.ref("/TEKYQ3/smh/I/Y3").on("value", function(snapshot){
    var ssled = snapshot.val();
    if(ssled==1){
        document.getElementById("unact" + Y3).style.display = "block";
		document.getElementById("act" + Y3).style.display = "none";
        document.getElementById("unst"+ Y3).style.display = "block";
		document.getElementById("ast"+ Y3).style.display = "none";
    }
    else{
        document.getElementById("unact"+ Y3).style.display = "none";
		document.getElementById("act"+ Y3).style.display = "block";
        document.getElementById("unst"+ Y3).style.display = "none";
		document.getElementById("ast"+ Y3).style.display = "block";
    }
})

//Y4
var Y4 = 4;
var onbt1 = document.getElementById("act"+ Y4);
onbt1.onclick = function(){
    database.ref("/TEKYQ3/smh/I").update({
        Y4 : 1
    });
}
var offbt1 = document.getElementById("unact"+ Y4);
offbt1.onclick = function(){
    database.ref("/TEKYQ3/smh/I").update({
        Y4 : 0
    });
}

database.ref("/TEKYQ3/smh/I/Y4").on("value", function(snapshot){
    var ssled = snapshot.val();
    if(ssled==1){
        document.getElementById("unact" + Y4).style.display = "block";
		document.getElementById("act" + Y4).style.display = "none";
        document.getElementById("unst"+ Y4).style.display = "block";
		document.getElementById("ast"+ Y4).style.display = "none";
    }
    else{
        document.getElementById("unact"+ Y4).style.display = "none";
		document.getElementById("act"+ Y4).style.display = "block";
        document.getElementById("unst"+ Y4).style.display = "none";
		document.getElementById("ast"+ Y4).style.display = "block";
    }
})

//Y5
var Y5 = 5;
var onbt1 = document.getElementById("act"+ Y5);
onbt1.onclick = function(){
    database.ref("/TEKYQ3/smh/I").update({
        Y5 : 1
    });
}
var offbt1 = document.getElementById("unact"+ Y5);
offbt1.onclick = function(){
    database.ref("/TEKYQ3/smh/I").update({
        Y5 : 0
    });
}

database.ref("/TEKYQ3/smh/I/Y5").on("value", function(snapshot){
    var ssled = snapshot.val();
    if(ssled==1){
        document.getElementById("unact" + Y5).style.display = "block";
		document.getElementById("act" + Y5).style.display = "none";
        document.getElementById("unst"+ Y5).style.display = "block";
		document.getElementById("ast"+ Y5).style.display = "none";
    }
    else{
        document.getElementById("unact"+ Y5).style.display = "none";
		document.getElementById("act"+ Y5).style.display = "block";
        document.getElementById("unst"+ Y5).style.display = "none";
		document.getElementById("ast"+ Y5).style.display = "block";
    }
})


//Y6
var Y6 = 6;
var onbt1 = document.getElementById("act"+ Y6);
onbt1.onclick = function(){
    database.ref("/TEKYQ3/smh/I").update({
        Y6 : 1
    });
}
var offbt1 = document.getElementById("unact"+ Y6);
offbt1.onclick = function(){
    database.ref("/TEKYQ3/smh/I").update({
        Y6 : 0
    });
}

database.ref("/TEKYQ3/smh/I/Y6").on("value", function(snapshot){
    var ssled = snapshot.val();
    if(ssled==1){
        document.getElementById("unact" + Y6).style.display = "block";
		document.getElementById("act" + Y6).style.display = "none";
        document.getElementById("unst"+ Y6).style.display = "block";
		document.getElementById("ast"+ Y6).style.display = "none";
    }
    else{
        document.getElementById("unact"+ Y6).style.display = "none";
		document.getElementById("act"+ Y6).style.display = "block";
        document.getElementById("unst"+ Y6).style.display = "none";
		document.getElementById("ast"+ Y6).style.display = "block";
    }
})













//Web Reiceive DHT11 fire
database.ref("/IOT/humd").on("value", function(snapshot){
    var humd = snapshot.val();
    document.getElementById("humd").innerHTML = humd;
})
database.ref("/IOT/temp").on("value", function(snapshot){
    var temp = snapshot.val();
    document.getElementById("temp").innerHTML = temp;
})
//Web Reiceive RAIN SENSOR fire
database.ref("/IOT/rainfall").on("value", function(snapshot){
    var rain = snapshot.val();
    document.getElementById("rain").innerHTML = rain;
})
