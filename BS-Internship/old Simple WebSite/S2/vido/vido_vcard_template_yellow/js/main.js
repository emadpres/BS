/*
* Theme Name: Vido - Responsive vCard & Portfolio Template
* Author: lmtheme (Linar Miftakhov)
* Author URL: http://themeforest.net/user/lmtheme
* Version: 1.0
*/
	// --------------------------------------------------------------------------	
	// Subpage Slider -----------------------------------------------------------
	// --------------------------------------------------------------------------
    jQuery(document).ready(function ($) {

      //Stellar.js
      $(window).stellar();

      var links = $('.navigation').find('li');
      slide = $('.slide');
      button = $('.button');
      mywindow = $(window);
      htmlbody = $('html,body');

      function goToByScroll(dataslide) {
          htmlbody.animate({
              scrollTop: $('.slide[data-slide="' + dataslide + '"]').offset().top-0
          }, 800, 'easeInOutQuint');
      }

      links.click(function (e) {
          e.preventDefault();
          dataslide = $(this).attr('data-slide');
          goToByScroll(dataslide);
      });

      button.click(function (e) {
          e.preventDefault();
          dataslide = $(this).attr('data-slide');
          goToByScroll(dataslide);

    });	
	
	// --------------------------------------------------------------------------	
	// tooltips -----------------------------------------------------------------
	// --------------------------------------------------------------------------
	$('.tip[title]').qtip({
		position:{
			my: 'bottom center',
			at: 'top center',
			adjust: {
				x: 0,
				y: -35
			}
		},
		style: {
			classes: 'qtip-custom'
		}		
	});

    // --------------------------------------------------------------------------
	// Google map container -----------------------------------------------------
	// --------------------------------------------------------------------------	
    $('.gmap').mobileGmap({
         deviceWidth: 480, // The select will be added for screensizes smaller than this
    });		
	
});