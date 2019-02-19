

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
  var db = firebase.firestore();
