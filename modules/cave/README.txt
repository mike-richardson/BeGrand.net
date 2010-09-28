; $Id: README.txt,v 1.1.2.1 2009/06/26 12:21:14 danielb Exp $

CONTENTS OF THIS FILE
----------------------

  * Introduction
  * Installation
  * Configuration
  * Usage
  

INTRODUCTION
------------
Maintainer: Daniel Braksator (http://drupal.org/user/134005)

Project page: http://drupal.org/project/cave.


INSTALLATION
------------
1. Copy cave folder to modules (usually 'sites/all/modules') directory.
2. At 'admin/build/modules' enable the cave module and the cave PHP module.


CONFIGURATION
-------------
1. Enable permissions at 'admin/user/permissions'.  Any roles with the
   'endure cave' permission and without the 'administer cave' permission
   will have their posts hidden from other users by default.
2. Configure cave at 'admin/user/cave'.


USAGE
-----
Use the Troll module to "blacklist" the user's IP addresses for Cave.  Troll is
available at http://drupal.org/project/troll.