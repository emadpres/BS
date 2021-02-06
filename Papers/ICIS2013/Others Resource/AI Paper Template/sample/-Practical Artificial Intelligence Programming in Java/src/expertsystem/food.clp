;;  File:  food.clp
;;
;;  A simple example to introdue CLIPS/Jess programming
;;
;;  To execute: java jess.Main food.clp

(deftemplate have_food 
   (slot name)
   (slot weight)
   (slot is_frozen (default no)))

(defrule startup "This is executed when (reset) (run) is executed"
  =>
  (assert (have_food (name spinach) (weight 10)))
  (assert (have_food (name peas) (weight 14) (is_frozen yes))))

(defrule thaw-frozen-food ""
  ?fact <- (have_food (name ?name) (is_frozen yes) (weight ?w))
  =>
  (retract ?fact)
  (assert (have_food (name ?name) (weight ?w) (is_frozen no)))
  (printout t "Using the microwave to thaw out " ?name crlf)
  (printout t "Thawing out " ?name " to produce "
     ?w " ounces of " ?name crlf))

(reset)
(run)
