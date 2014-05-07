
/**
 *  @file
 *  This file handles the JS for tabs2.
 */

(function($) {

  /**
   * Loads media browsers and callbacks, specifically for media as a field.
   */
  Drupal.behaviors.tabs2 = {
    attach: function(context, settings) {

      if (settings.tabs2 != undefined) {
        for (var selector in settings.tabs2) {
          // Currently simply provide a
          var specs = settings.tabs2[selector];

          specs.heightStyle = 'auto';

          // Add select event to update url in the browser and manage the tab
          // height to avoid jumping to top of the page.
          // @see http://stackoverflow.com/questions/243794/jquery-ui-tabs-causing-screen-to-jump
          specs.select = function(event, ui) {
            // Change the url to match the currently selected tab.
            window.location.hash = ui.tab.hash;

            var selectedIndex = $(this).tabs('option', 'selected');

            // When the selected index matches the current item, we are about
            // to collapse the element, so do not alter the height.
            if (selectedIndex == ui.index) {
              // In this case, we will have en empty hash for the url, but also
              // have to take care of scrolling.
              // @see http://stackoverflow.com/questions/4715073/window-location-hash-prevent-scrolling-to-the-top
              var scr = document.body.scrollTop;
              window.location.hash = ' ';
              document.body.scrollTop = scr;
            }
            // We also do nothing in the case the element is collapsed.
            else if (selectedIndex < 0) {
              // Nothing.
            }
            else {
              $(this).css('height', $(this).height());
            }
          };

          // Reset the container height again, when the tab has been opened.
          specs.show = function(event, ui) {
            $(this).css('height', 'inherit');
          };

          $(selector).once('tabs2-processing').tabs(specs);
        }

      }
    }
  };
})(jQuery);

