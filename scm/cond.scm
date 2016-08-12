(define pred (lambda (x)
  (cond
    ((eq? 1 x) 1337)
    ((eq? 2 x) 99999)
    (else 1412))))

(pred 1)
(pred 2)
(pred 3)
(pred 4)
(pred 5)
