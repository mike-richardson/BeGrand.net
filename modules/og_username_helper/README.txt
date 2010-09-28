$Id

-- SUMMARY --

This module try to help OG administrators to add site users to their OG
by providing an autocomplete input(like the one you can see editing core
node user author).

This module start as a patch for OG: "More convenient way to add users"
(http://drupal.org/node/225308)
And almost 2 years after, it seem to be a good idea to maintain it as a
separate module.

You can see it in action: http://blip.tv/file/2921743

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/og_username_helper


-- REQUIREMENTS --

OG module: http://drupal.org/project/og


-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further
  information.


-- CONFIGURATION --

* Configure user permissions in Administer >> User management >>
  Permissions >> og_username_helper module:

  - access og username helper

    Users in roles with the "access og username helper" permission will
    see the autocomplete input to insert usernames.


-- CONTACT --

Current maintainers:
* Marco Villegas (marvil07) - http://drupal.org/user/132175


