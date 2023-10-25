import { initializeApp } from "https://www.gstatic.com/firebasejs/10.3.1/firebase-app.js";
import { getDatabase, ref, set } from "https://www.gstatic.com/firebasejs/10.3.1/firebase-database.js";

const firebaseConfig = {
    apiKey: "AIzaSyAQaomtgqmPoNwHB66MMlF76KoFYvwZics",
    authDomain: "trafficmechansim.firebaseapp.com",
    databaseURL: "https://trafficmechansim-default-rtdb.firebaseio.com",
    projectId: "trafficmechansim",
    storageBucket: "trafficmechansim.appspot.com",
    messagingSenderId: "1009488772575",
    appId: "1:1009488772575:web:7b639a869c9b133512586a",
    measurementId: "G-N3K0EDWH8P"
  };

  
// Initialize Firebase
const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

export function LED_RED() {
    set(ref(database, "light/"), {
        light: "RED"
    });
}

export function LED_BLUE() {
    set(ref(database, "light/"), {
        light: "BLUE"
    });
}

export function LED_GREEN() {
    set(ref(database, "light/"), {
        light: "GREEN"
    });
}

export function LED_OFF() {
    set(ref(database, "light/"), {
        light: "OFF"
    });
}