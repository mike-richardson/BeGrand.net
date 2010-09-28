// $Id: README.txt

DESCRIPTION
-----------
This module was created to answer the following requirements:
1. Show a series of slides using the fade effect.
2. Allow the content manager (non admin role) to control the contents of each slide.
3. Allow the content manager to publish / unpublish slides.
4. Allow the content manager to set the order by which slide appear.
5. Allow the content manager to set the slides intervals.
6. Best performance - do not load all images during the initial page load but rather load each slide before presented.
7. Have a frontpage content that will appear before the slideshow starts.
  

INSTALLATION
------------
- Place entire ajaxs_slideshow folder in the Drupal modules directory, or relevant site module directory.
- Enable the module inside the modules page using the admin account.
At this point your slideshow is already operational. under the path <www.my-domain.com>/slideshow-front you can view the slideshow. 
Initially it consists of all published nodes within your site.

To further control the slideshow do the following:  
- Under the views area, you will find a new view named ajax_slideshow_view. To better control the filtering and sorting of your slideshow use this view.
Do not change any other data element accept of the filters and sorting. 
- go into the ajax_slideshow admin page and setup the following:
1. Frontpage node nid - nid of the node which will be used as an introduction content to the slideshow (while the slideshow loads).
2. Slide duration - pace of changing the slides.
3. Slideshow height - since the nodes being presented might have varying heights this parameter sets the fixed height of the presentation. This way when slides are changing additinal content on screen won't re-position itself.

For any questions / comments please contact us at contact@dofinity.com

enjoy.   