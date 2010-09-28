$Id: README.txt,v 1.1 2010/05/12 00:40:32 pglatz Exp $

nodedump module
===============
Sometimes you need to take a quick look at the contents of a node during the 
development process. There are many ways to do this; using phpmyadmin, running a 
mysql query from the command line, using drush, using the devel module, etc. 
Here is an alternative that provides a GUI method.

This module provides a quick and dirty way to dump a node's details to the 
screen. Enter a node id, submit, and there you go.

After installation, you'll see the Node Dumper command on your Content 
Management menu (admin/content/nodedump).

Access is limited to site administrators.

The last nid requested is stored in the conf variable "nodedump_last_nid".


Theming
-------
The output of the dump is enclosed in a division called nodedumper.

The dump itself contains the created and changed fields of the node displayed in 
a human-friendly format, followed by a print_r of the node itself. In order to 
preserve indentation, the leading blanks on each line before the first non-blank 
character are converted to non-breaking spaces, and everything is put in a tt 
style.

Here's an example of a style setting you can put in one of your site style 
sheets:

.nodedumper tt {
  color: black;
  font-size: 92%;
  line-height: 1.0;
  white-space: nowrap;
}




Author
------
Phil Glatz <drupal@glatz.com>
www.glatz.com
