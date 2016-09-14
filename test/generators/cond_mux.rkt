#lang racket

(require "common.rkt")

(define mux2slug '(lambda (a b x)
                    (cond
                      [(and (not a) (not x)) #f]
                      [(and a (not x)) #t]
                      [(and (not b) x) #f]
                      [else #t])))

(define mux4slug '(lambda (a b c d x y)
                    (cond
                      [(not x) (mux2 a b y)]
                      [else (mux2 c d y)])))

(define mux8slug '(lambda (a b c d e f g h x y z)
                    (cond
                      [(not x) (mux4 a b c d y z)]
                      [else (mux4 e f g h y z)])))

(define mux16slug '(lambda (a b c d e f g h i j k l m n o p w x y z)
                     (cond
                       [(not w) (mux8 a b c d e f g h x y z)]
                       [else (mux8 i j k l m n o p x y z)])))


(generate-slug-testcase 'mux2 mux2slug (bit-lists 3))
(generate-slug-testcase 'mux4 mux4slug (bit-lists 6))
(generate-slug-testcase 'mux8 mux8slug (bit-lists 11))
(generate-slug-testcase 'mux16 mux16slug (take (bit-lists 20) 10000))
