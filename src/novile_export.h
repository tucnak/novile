/*
 * This file is part of the Novile Editor
 * This program is free software licensed under the GNU LGPL. You can
 * find a copy of this license in LICENSE in the top directory of
 * the source code.
 *
 * Copyright 2013    Illya Kovalevskyy   <illya.kovalevskyy@gmail.com>
 *
 */

#ifndef NOVILE_EXPORT_H
#define NOVILE_EXPORT_H

#include <QtCore/qglobal.h>

/**
 * @mainpage Welcome to the API documentation
 *
 * @section sec_intro Introduction
 *
 * Novile is an editor for Qt 5, based on Ace editor from ajax.org. It allows to extend your
 * application with pretty source code editor, full of features.
 *
 * If you ask us to describe it in 5 words, we will say: beautiful, powerful, extensible,
 * light-weight and just awesome. Created with Qt 5, created for Qt 5 - Novile offers the
 * biggest cross-platform power you can even think about. Enjoy it!
 *
 * @section sec_moreAce More about Ace
 *
 * Ace is an embeddable code editor written in JavaScript. It matches the features and
 * performance of native editors such as Sublime, Vim and TextMate. It can be easily
 * embedded in any web page and JavaScript application. Ace is maintained as the primary
 * editor for Cloud9 IDE and is the successor of the Mozilla Skywriter (Bespin) project.
 *
 * Its main features are:
 *
 * <ul>
 *     <li>Syntax highlighting for over **60** languages (TextMate/Sublime Text.tmlanguage
 *     files can be imported)</li>
 *
 *     <li>Over **20** themes (TextMate/Sublime Text .tmtheme files can be imported)</li>
 *
 *     <li>Automatic indent and outdent</li>
 *
 *     <li>An optional command line</li>
 *
 *     <li><b>Handles huge documents (four million lines seems to be the limit!)</b></li>
 *
 *     <li>Fully customizable key bindings including vim and Emacs modes</li>
 *
 *     <li><b>Search and replace with regular expressions</b></li>
 *
 *     <li>Highlight matching parentheses</li>
 *
 *     <li>Toggle between soft tabs and real tabs</li>
 *
 *     <li>Displays hidden characters</li>
 *
 *     <li>Drag and drop text using the mouse</li>
 *
 *     <li>Line wrapping</li>
 *
 *     <li><b>Code folding</b></li>
 *
 *     <li>Multiple cursors and selections</li>
 *
 *     <li><b>Live syntax checker</b> (currently JavaScript/CoffeeScript/CSS/XQuery)</li>
 *
 *     <li>Cut, copy, and paste functionality</li>
 * </ul>
 *
 * @section sec_install Installation
 *
 * All installation notes and guides are in the INSTALL file, I hope it's enough to understand
 * how Novile build system works and which magic you can perform with it. Listing INSTALL file
 * here will cause unsynchronization: actually, I dislike unsynchronization :)
 *
 */

#ifndef NOVILE_EXPORT
# if defined(NOVILE_MAKEDLL)
#  define NOVILE_EXPORT Q_DECL_EXPORT
# else
#  define NOVILE_EXPORT Q_DECL_IMPORT
# endif
#endif

#endif // NOVILE_EXPORT_H
