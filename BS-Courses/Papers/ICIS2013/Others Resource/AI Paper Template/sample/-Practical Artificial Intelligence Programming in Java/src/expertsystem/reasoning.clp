;;  File:  reasoning.clp
;;
;;  A simple example to introduce CLIPS/Jess programming
;;
;;  To execute: java jess.Main reasoning.clp

(deftemplate block
   (slot name)
   (slot on_top_of (default table))
   (slot supporting (default nothing)))

(deftemplate old_block_state
   (slot name)
   (slot on_top_of (default table))
   (slot supporting (default nothing)))

(deftemplate goal
   (slot supporting_block)
   (slot supported_block))

(defrule startup "This is executed when (reset) (run) is executed"
  =>
  (assert (goal (supporting_block C) (supported_block A)))
  (assert (block (name A) (supporting B)))
  (assert (block (name B) (on_top_of A) (supporting C)))
  (assert (block (name C) (on_top_of B)))
  (assert (block (name D)))
  (assert (block (name table) (supporting A)))
  (assert (block (name table) (supporting C))))

(defrule set-block-on "move ?block_1 to ?block_2 if both are clear"
  ?fact1 <- (block (name ?block_1) (on_top_of ?on_top_of_1) (supporting nothing))
  ?fact2 <- (block (name ?block_2&:(neq ?block_2 ?block_1)) (supporting nothing) (on_top_of ?on_top_of_2))
  ?fact3 <- (block (name ?on_top_of_1) (supporting ?block_1) (on_top_of ?on_top_of_3))
  (not (old_block_state (name ?block_2) (on_top_of ?on_top_of_2) (supporting ?block_1)))
  =>
  (retract ?fact1)
  (retract ?fact2)
  (retract ?fact3)
  (assert (block (name ?block_1) (on_top_of ?block_2) (supporting nothing)))
  (assert (block (name ?block_2) (on_top_of ?on_top_of_2) (supporting ?block_1)))
  (assert (old_block_state (name ?block_2) (supporting nothing) (on_top_of ?on_top_of_2)))
  (assert (block (name ?on_top_of_1) (supporting nothing) (on_top_of ?on_top_of_3)))
  (printout t "Moving " ?block_1 " from " ?on_top_of_1 " to " ?block_2 crlf))

(defrule clear-block "remove ?block_1 from ?block_2 if ?block1 is clear"
  ?fact1 <- (block (name ?block_1) (on_top_of ?block_2&:(neq ?block_2 table)) (supporting nothing))
  ?fact2 <- (block (name ?block_2) (supporting ?block_1) (on_top_of ?on_top_of_2))
  =>
  (retract ?fact1)
  (retract ?fact2)
  (assert (block (name ?block_1) (on_top_of table) (supporting nothing)))
  (assert (block (name ?block_2) (on_top_of ?on_top_of_2) (supporting nothing)))
  (assert (block (name table) (supporting ?block_1)))
  (printout t "Clearing " ?block_1 " from " ?block_2 " on to table" crlf))

(defrule my-halt-rule "to stop when the goal is reached"
  (declare (salience 100))
  (goal (supporting_block ?b1) (supported_block ?b2))
  (block (name ?b1) (supporting ?b2))
  =>
  (printout t "Done: goal is satisfied" crlf)
  (halt))

(set-strategy breadth)
(reset)
(run 20)
(printout t crlf "Facts in system at the end of the run:" crlf)
(facts)
