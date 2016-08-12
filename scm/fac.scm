(define fac (lambda (n)
  (or
   (and (zero? n) 1)
   (* n (fac (- n 1))))))

(fac 0)
(fac 1)
(fac 4)
(fac 10)
(fac 100)
