(define foldl (lambda (proc start li)
                (or
                 (and (empty? li) start)
                 (foldl proc (proc start (first li)) (rest li)))))

(define map (lambda (proc li)
              (or
               (and (empty? li) empty)
               (cons (proc (first li)) (map proc (rest li))))))

(foldl + 0 (cons 1 (cons 2 (cons 3 (cons 4 (cons 5 empty))))))
(map (lambda (x) (* 100 x)) (cons 1 (cons 2 (cons 3 (cons 4 (cons 5 empty))))))
