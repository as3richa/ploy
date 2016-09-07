#lang racket

(define count 500)
(define maximum-params 8)
(define maximum-depth 8)

(define maximum-literal 4294967086)
(define literal-probability 0.3)

(define operations (vector
                    (cons + '+)
                    (cons - '-)
                    (cons * '*)
                    (cons / '/)))

(define (random-expr max-depth)
  (cond
    [(zero? max-depth) (random-literal)]
    [else (let
              [(operation (random (add1 (vector-length operations))))]
            (if (<= (random) literal-probability)
                (random-literal)
                (let* [
                       (op (vector-ref operations (random (vector-length operations))))
                       (op-fn (car op))
                       (op-sym (cdr op))
                       (params (random-expr-list (random (add1 maximum-params)) (sub1 max-depth)))
                       (param-trees (map car params))
                       (param-values (map cdr params))]
                  (cons
                   (cons op-sym param-trees)
                   (apply op-fn param-values)))))]))

(define (random-literal) (let [(r (random (add1 maximum-literal)))]
                           (cons r r)))

(define (random-expr-list count max-depth)
  (with-handlers ([exn:fail? (lambda (exn) (random-expr-list count max-depth))])
    (if (zero? count)
        empty
        (cons (random-expr max-depth) (random-expr-list (sub1 count) max-depth)))))

(define (ploy-rational n)
  (if (= (denominator n) 1)
      (number->string n)
      (string-append "(/ " (number->string (numerator n)) " " (number->string (denominator n)) ")")))

(for-each
 (lambda (v)
   (write (car v)) (newline)
   (fprintf (current-error-port) "~a\n" (ploy-rational (cdr v))))
 (random-expr-list count maximum-depth))
