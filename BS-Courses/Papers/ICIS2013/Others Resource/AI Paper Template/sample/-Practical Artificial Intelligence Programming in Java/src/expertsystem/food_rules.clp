;;  File:  food.clp
;;
;;  A simple example to introdue CLIPS/Jess programming
;;
;;  To execute: java jess.Main food.clp

(deftemplate have_food 
   (slot name)
   (slot weight)
   (slot is_frozen (default no)))

(defrule thaw-frozen-food ""
  ?fact <- (have_food (name ?name) (is_frozen yes) (weight ?w))
  =>
  (retract ?fact)
  (assert (have_food (name ?name) (weight ?w) (is_frozen no)))
  (printout t "Using the microwave to thaw out " ?name crlf)
  (printout t "Thawing out " ?name " to produce "
     ?w " ounces of " ?name crlf)
  (assert (cooked-food ?name used-microwave)))

