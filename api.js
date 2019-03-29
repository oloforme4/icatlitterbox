
// Initialize Firebase
var config = {
  apiKey: "AIzaSyC9Ij3Dr2KkojeQQMBBZkYFwMbhwBp8klg",
  authDomain: "icatlitterbox.firebaseapp.com",
  databaseURL: "https://icatlitterbox.firebaseio.com",
  projectId: "icatlitterbox",
  storageBucket: "icatlitterbox.appspot.com",
  messagingSenderId: "463560272551"
};
firebase.initializeApp(config);
const db = firebase.firestore();
//db.settings({ timestampsInSnapshots: true });

$('.bar-percentage[data-percentage]').each(function () {
  var progress = $(this);
  var percentage = Math.ceil($(this).attr('data-percentage'));
  $({countNum: 0}).animate({countNum: percentage}, {
    duration: 2000,
    easing:'linear',
    step: function() {
      // What todo on every count
    var pct = '';
    if(percentage == 0){
      pct = Math.floor(this.countNum) + '%';
    }else{
      pct = Math.floor(this.countNum+1) + '%';
    }
    progress.text(pct) && progress.siblings().children().css('width',pct);
    }
  });
});