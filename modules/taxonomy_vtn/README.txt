$Id: README.txt,v 1.1.2.6 2009/06/15 20:21:06 alexiswilke Exp $


  About Taxonomy VTN
=======================

This module provides an index that looks like a paper book index for vocabularies,
terms and nodes.

It supports synonyms, descriptions, multi-columns, letter headers with a set of
quick links at the top to reach the letter you are looking for.

For a list of capabilities, you want to visit our project page. It includes all
the info you need to know about.

   http://drupal.org/project/taxonomy_vtn


o Dependencies

  The core Taxonomy module must be turned on.

  The contribution module named Views is optional.


o Databases

  This module is Drupal 6.x database compliant.



  INSTALLATION
================

  1. Install the files under sites/all/modules

  2. Turn on the Taxonomy VTN module on the administer modules page

  2.1 The Taxonomy VTN module gives you the taxonomy_vtn and sub-pages

  2.2 The Taxonomy VTN Vocabulary Block gives you one block that displays
      all the vocabularies.

  2.3 The Taxonomy VTN Terms Block gives you one block per vocabulary
      that displays the terms of the vocabulary

  3. The files in the po folder are optional (Translations)

  4. Configure access rights for users and visibility settings if you
     turn on Taxonomy VTN Blocks (admin/user/permissions).

  Now you have a "Site index" in your Navigation menu.


  CONFIGURATION
=================

  1. Global

  The main configuration page is admin/settings/taxonomy_vtn
  You can configure the main taxonomy_vtn page and some defaults for the
  terms pages.

  2. Details

  Each taxonomy has a set of options to define the display of the
  Terms and the Nodes.

  Note that when the Terms setup is defined to point to the default
  Drupal term page, or a view, the Nodes options are ignore.

  3. Blocks

  The Vocabulary and Terms blocks are administered within the Block
  interface. admin/build/blocks


  USING
=========

  For the Taxonomy VTN module to be useful, you need to have:

  * At least one vocabulary
  * The vocabulary should be marked as "Multiple Terms"
  * The vocabulary should have some terms defined

  Then you will see the result under taxonomy_vtn as in:

     http://www.example.com/taxonomy_vtn

  To create a vocabulary, go to admin/content/taxonomy and click on
  Add Vocabulary.


  Some vocabularies, such as your list of forums, you may want to
  hide. To do so, go to the global configuration page and enter
  the vocabulary number that should be omitted.

