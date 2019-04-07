// firebase register & login
var config = {
    apiKey: "AIzaSyC9Ij3Dr2KkojeQQMBBZkYFwMbhwBp8klg",
    authDomain: "icatlitterbox.firebaseapp.com",
    databaseURL: "https://icatlitterbox.firebaseio.com",
    projectId: "icatlitterbox",
    storageBucket: "icatlitterbox.appspot.com",
    messagingSenderId: "463560272551"
  };
  firebase.initializeApp(config);
function saveData() {

    var firstname = document.getElementById('first_name');
    var lastname = document.getElementById('last_name');
    var displayname = document.getElementById('display_name');
    var email = document.getElementById('email');
    var password = document.getElementById('password');
    var confirmpassword = document.getElementById('password_confirmation');

    var firstnameV = document.getElementById('first_name').value;
    var lastnameV = document.getElementById('last_name').value;
    var displaynameV = document.getElementById('display_name').value;
    var emailV = document.getElementById('email').value;
    var passwordV = document.getElementById('password').value;
    var confirmpasswordV = document.getElementById('password_confirmation').value;


    if (firstnameV == "") {
        swal("Oops...", "First Name must be filled out", "error");
        return false;
    }
    else if (lastnameV == "") {
        swal("Oops...", "Last Name must be filled out", "error");
        return false;
    }
    else if (displaynameV == "") {
        swal("Oops...", "DisplayName must be filled out", "error");
        return false;
    }
    else if (passwordV != confirmpasswordV) {
        swal("Oops...", "Password no Match!", "error");
        return false;
    }
    else {
        insertData(first_name.value, last_name.value, display_name.value, email.value, password.value, password_confirmation.value)
        console.log('insertData Process!');
    }
}

function insertData(first_name, last_name, display_name, email, password, password_confirmation) {

    var firebaseRef = firebase.database().ref("users");
    firebaseRef.push({
        firstname: first_name,
        lastname: last_name,
        displayname: display_name,
        email: email,
        password: password,
        confirmpassword: password_confirmation
    });

    console.log("Insert Success");
    signUp();
}

function signUp() {
    const email_register = document.getElementById('email').value;
    const password_register = document.getElementById('password').value;
    const auth = firebase.auth();
    const promise = auth.createUserWithEmailAndPassword(email_register, password_register);

    promise
        .then(
            function (result) {
                swal("Congrats!", ", Your account is created!", "success").then(function () {

                    window.location.href = "index.html"

                });


                firebase.auth().signOut()
            }

        )

        .catch(error => {
            // Handle Errors here.
            var errorMessage = error.message;
            swal("Oops...", errorMessage, "error");
        });
}


function signIn() {
    var email = document.getElementById('email_login').value;
    var password = document.getElementById('password_login').value;

    firebase.auth().signInWithEmailAndPassword(email, password).then(
        function (result) {

            swal("You are log in", email, "success", { button: false });

            setTimeout(function () {
                location.reload();
            }, 2500);

        }

    )
        .catch(function (error) {
            var errorCode = error.code;
            var errorMessage = error.message;
            if (errorCode === 'auth/wrong-password') {
                swal("Wrong password", "Please check Caps-Lock Button and try again", "error");
            } else {
                swal(errorMessage);
            }
        });
}
firebase.auth().onAuthStateChanged(function (user) {

    if (user) {
        // User is signed in.
        console.log('logined user12324');
        console.log(user)
        document.getElementById("BtnLogin").style.display = "none";    //close
        document.getElementById("BtnRegister").style.display = "none";
        document.getElementById("BtnLogout").style.display = "inline-block"; //open
        document.getElementById("LbLogout").style.display = "inline-block"; //open
        document.getElementById("hideNolog").style.display = "inline-block";
        var user = firebase.auth().currentUser;
        var email_id = user.email;
        document.getElementById("LbLogout").innerHTML = email_id;
    } 
    else {
        // No user is signed in.
        console.log('No User login');
        document.getElementById("BtnLogout").style.display = "none";
        document.getElementById("BtnLogin").style.display = "inline-block";
        document.getElementById("hideNolog").style.display = "none";
    }
});

function logout() {
    firebase.auth().signOut().then(
        function (result) {
            swal("Good Bye!", "You are Logout!", "warning").then(function () {

                window.location.href = "index.html"

            });
            console.log('Logout!')

        }
    )
}

