#lang racket

(require racket/path)

(define args
  (command-line
   #:program "test-runner"
   #:args (executable tests-directory)
   (cons executable tests-directory)))

(define executable (car args))
(define tests-directory (cdr args))

(define test-timeout 5)

(define tests (if (equal? (filename-extension tests-directory) #"ply")
                  (list tests-directory)
                  (find-files
                   (lambda (path) (equal? (filename-extension path) #"ply"))
                   tests-directory)))

(define (cat path [default ""])
  (if (file-exists? path)
      (let* [(f (open-input-file path)) (content (port->string f))] (close-input-port f) content)
      default))

(define (exec input-path)
  (printf "     $ ~a ~a\n" executable input-path)
  (let-values
      [((proc stdout stdin stderr) (subprocess #f #f #f executable input-path))]
      (let
          [(output (port->string stdout))
           (proc (subprocess-wait proc))
           (status (subprocess-status proc))]
        (begin
          (close-input-port stdout)
          (close-output-port stdin)
          (close-input-port stderr)
          (cons status output)))))


(define (run-test input-path)
  (printf "===> Test ~a\n" input-path)
  (let*
      [(goal-output (cat (path-replace-suffix input-path #".out")))
       (exec-result (exec input-path))
       (real-status (car exec-result))
       (real-output (cdr exec-result))]
    (if (string=? real-output goal-output)
        (printf "     Output matches expectation. OK\n")
        (begin
          (printf "     Output does not match expectation. Re-run with ~a ~a\n" executable input-path)
          (error "Test failed")))))

(printf "Found ~a tests\n" (length tests))
(for-each run-test tests)
(printf "All ~a tests succeeded\n" (length tests))
