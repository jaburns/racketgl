#lang racket

(require ffi/unsafe
         ffi/unsafe/define
         ffi/unsafe/cvector)

(define KEY_RIGHT 1073741903)
(define KEY_LEFT  1073741904)
(define KEY_DOWN  1073741905)
(define KEY_UP    1073741906)

(define-ffi-definer define-shell (ffi-lib "racketglshell"))


(define-cstruct _RenderState ([red _float]
                             [green _float]
                             [blue _float]))

(define-cstruct _InputState ([num_keys_down _int]
                             [keys_down _pointer]))


(define-shell shell_open (_fun _string _int _int -> _void))
(define-shell shell_is_open (_fun -> _stdbool))
(define-shell shell_update (_fun _RenderState-pointer -> _void))
(define-shell shell_close (_fun -> _void))
(define-shell shell_borrow_input_state (_fun -> _InputState-pointer))
(define-shell shell_release_input_state (_fun _InputState-pointer -> _void))

(define (read-inputs)
  (let* ([x (shell_borrow_input_state)]
         [y (cvector->list (make-cvector* (InputState-keys_down x) _int (InputState-num_keys_down x)))])
    (shell_release_input_state x)
    y))


(define (clamp01 x)
  (cond
    [(< x 0.0) 0.0]
    [(> x 1.0) 1.0]
    [else x]))

(define (step-state state input)
  (let ([r (RenderState-red state)]
        [g (RenderState-green state)]
        [b (RenderState-blue state)]
        [lr (cond
              [(member KEY_LEFT input) -0.1]
              [(member KEY_RIGHT input) 0.1]
              [else 0.0])])
    (make-RenderState (clamp01 (+ r lr)) g b)))

(define (main-loop state)
  (when (shell_is_open)
    (let* ([input (read-inputs)]
           [new-state (step-state state input)])
      (shell_update new-state)
      (sleep (/ 1 60))
      (main-loop new-state))))

(define (run-game)
  (shell_open "Hello World" 640 480)
  (main-loop (make-RenderState 0.0 0.1 0.0)))