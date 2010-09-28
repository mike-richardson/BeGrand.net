$Id: README.txt,v 1.10.4.15 2009/09/12 03:08:23 michellec Exp $

CONTENTS OF THIS FILE
---------------------
 * Introduction
 * Installation

INTRODUCTION
------------
Advanced Profile Kit (http://drupal.org/project/advanced_profile) provides building
blocks for putting together fancy user profile pages like those commonly found on social
networking sites.

INSTALLATION
------------
(Note: This section is currently a dump of what's in the handbook page, HTML and all. Sometime before release I will clean this up and make it readable as a text file but I wanted to wait until I was sure the docs wouldn't be changing.)

Since this is a kit module, it is not necessary to install this exactly as directed. Depending on your experience, you can pick and choose which pieces to use to build your unique profiles. The instructions here will get you up and running with the standard APK profile.

<h2>Install and enable APK</h2>
<ol>
  <li>Copy the entire advanced_profile module directory into your normal directory for
     modules, usually sites/all/modules </li>
  <li>Enable Advanced Profile Kit in the "other" fieldset at ?q=admin/build/modules</li>
</ol>

<h2>Install modules that APK uses</h2>
(submodules needed are listed in parentheses)
<ul>
  <li><a href="http://drupal.org/project/author_pane">Author Pane 2.x</a> (Author pane) Also see the Author Pane project page for modules it supports to add more functionality.</li>
  <li><a href="http://drupal.org/project/panels">Panels 3.x</a> (Panels)</li>
  <li><a href="http://drupal.org/project/ctools">CTools</a> (Chaos Tools, Page Manager)</li>
  <li><a href="http://drupal.org/project/views">Views 2.x</a> (Views, Views content panes, Views UI)</li>
  <li><a href="http://drupal.org/project/cck">CCK 2.x</a> (Content, Content Copy, Fieldgroup, Option Widgets, Text)</li>
  <li><a href="http://drupal.org/project/content_profile">Content Profile</a></li>
  <li><a href="http://drupal.org/project/link">Link</a> (Link - grouped with CCK)</li>
  <li><a href="http://drupal.org/project/user_relationships">User Relationships</a> </li>
  <li>Statistics (part of core, needed for user visits pane)</li>
</ul> 

<h2>Configure Advanced Profile Kit</h2>
<ol>
  <li><em>Redirect from profile node to user page:</em> When using nodes as profiles, you have the node sitting out there just like other nodes. This redirect will prevent anyone from visiting that node as it will redirect them to the profile page of the owner of the profile node.
  <li><em>Number of entries:</em> Enter the number of profile visits to show at one time.</li>
  <li><em>Show only the last visit from each user:</em> If checked, a given person will only be listed once no matter how many times they visit.</li>
  <li><em>Granularity of time ago:</em> The granularity on the profile vists list defaults to 2. Set it to 1 to take up less room or to 3 for more precision.</em></li>
  <li><em>Roles to exclude:</em> Check any roles you don't want to show up on the list. Make note of the performance warning.</li></ol></li>
</ol>

<h2>Create the user profile node type</h2>
@TODO: This is currently changing... will right docs once the change is complete

<h2>Configure core</h2>
<ol>
  <li>Navigate to ?q=admin/user/settings and enable picture support if you want users to have avatars on their profiles.</li>
  <li>Configure statistics module:
    <ol>
      <li>Navigate to ?q=admin/reports/settings</li>
      <li>Enable access log: Enabled</li>
    </ol>
  </li>
</ol>

<h2>Set access control</h2>
<ol>
  <li>Navigate to ?q=admin/user/permissions</li>
  <li>Enable "administer advanced profile" for your admins</li>
  <li>Enable "access user profiles" for everyone that you want to be able to view user profiles.</li>
  <li>Enable "edit any uprofile content" for your admins so they can edit anyone's profile.
  <li>Allow users to create profile nodes by giving them access to "create uprofile content" and "edit own uprofile content". You will not want to give them delete perms.
</ol>

<h2>Configure the user profile page</h2>
<ol>
  <li>Navigate to ?q=admin/build/pages</li>
  <li>Enable the "user_view" system page. If this is not enabled, APK cannot take over the user profile page. If you are using APK in a custom way and don't wish to use it with Page Manager, you can leave this disabled.</li>
  <li>Once it is enabled, click edit on "user_view".</li>
  <li>If you like how APK looks by default, you don't need to make any changes. But you should poke around here to see what's available to you for customizing your profile.</li>
</ol>
