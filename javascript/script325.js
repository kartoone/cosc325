document.addEventListener("DOMContentLoaded", (event) => {
    var goButton = document.getElementById('gobutton');
    goButton.onclick = function(event) {
      event.preventDefault(); // proper way to prevent form submission
      this.style.background = 'red';
      this.style.color = 'white';
      var lis = processList(); // side-effect of populating our global lis with the data 
      console.log(foo((lis) => lis.map((a)=>a%2).filter((a)=>a!=0).reduce((a,b)=>a+b,0)), lis);
      return false; // old school way of preventing form submission
  
    }

});

const foo = function (func, lis) {
  return func(lis);
};



function processList() {
  // these two statements won't work, even if called from 
  // the button's onclick handler b/c processList is outside
  // of the button ... therefore its referencing environment
  // is different than if you put the code below directly
  // inside the handler
  // this.style.background = "red";
  // this.style.color = "white";
  var origlis = getData();
  var lis = callMap(origlis)
  lis = callFilter(lis)
  lis = callReduce(lis)
  callMFR(origlis)
  return origlis;
}

function getData() {
  return document.getElementById('inputdata').value.split(",").map(Number);
}


// demonstrate map by adding 1 to each item in the list
// and displaying the results in the mapresults <pre> tag
function callMap(lis) {
  lis = lis.map((a)=>a%2);
  document.getElementById('mapresults').innerHTML = lis.join(',');
  return lis;
}

function callFilter(lis) {
  lis = lis.filter((a)=>a!=0);
  document.getElementById('filresults').innerHTML = lis.join(',');
  return lis;
}

function callReduce(lis) {
  var sum = lis.reduce((a,b)=>a+b);
  document.getElementById('redresults').innerHTML = sum;
  return lis;
}

// counts how many odds are in a list
function callMFR(lis) {
  var postmap = lis.map((a)=>a%2);
  var postfilter = postmap.filter((a)=>a!=0);
  var sum = postfilter.reduce((a,b)=>a+b,0);
  document.getElementById('mfrresults').innerHTML = sum;
  return lis;
}
