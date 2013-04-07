/*
 * This file is part of the Novile Editor
 * This program is free software licensed under the GNU LGPL. You can
 * find a copy of this license in LICENSE in the top directory of
 * the source code.
 *
 * Copyright 2013    Illya Kovalevskyy   <illya.kovalevskyy@gmail.com>
 *
 */

function property(param, value) {
    if (arguments.length == 1) {
        // Get
        return sessionStorage[param];
    } else {
        // Set
        sessionStorage[param] = value;
    }
}

property("lines", 1);
property("text", "");

var timerid = -1;

// All necessary calls here
function handleEvents() {
    var newLines = editor.session.getLength();
    if (newLines != property("lines")) {
        property("lines", newLines);
        Novile.onLinesChanged(newLines);
    }

    var newText = editor.getValue();
    if (newText != property("text")) {
        property("text", newText);
        Novile.onTextChanged();
    }

    clearTimeout(timerid);
    timerid = -1;
}

// On each change with the editor
// Some events haven't been finished yet
// Thats why we schedule it
editor.on('change', function() {
    if (timerid > 0) {
        clearTimeout(timerid);
    }

    timerid = setTimeout(handleEvents, 50);
});
