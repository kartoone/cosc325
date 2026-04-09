#lang racket
(define test_data '(10 20 3 4 5 6 7 1 2 10))

; recursive function to add up all the numbers in a list
(define (suml lis)
  (if (= (length lis) 1)
      (car lis)
      (+ (car lis) (suml (cdr lis)))))

; no error checking
(define (avgl lis)
  (/ (suml lis) (length lis)))

; with error checking
(define (avglc lis)
  (if (empty? lis)
      (print "error")
      (/ (suml lis) (length lis))))

; min element in list
;  base case - 1 item list, that 1 item is the min
;  recursive step - tricky!
(define (minl lis)
  (if (= (length lis) 1)
      (car lis)
      (if (< (car lis) (minl (cdr lis)))
          (car lis)
          (minl (cdr lis)))))

(define (maxl lis)
  (if (= (length lis) 1)
      (car lis)
      (if (> (car lis) (maxl (cdr lis)))
          (car lis)
          (maxl (cdr lis)))))

(define (min_using_let lis)
  (if (= (length lis) 1)
      (car lis)
      (let (
            (headitem (car lis))
            (mintail (min_using_let (cdr lis)))
           )
        (if (< headitem mintail)
            headitem
            mintail))))

; reversing a list is tricky recursion
; base case - list is empty ===> empty list
; recursive step - list is not empty ===> append the head item to the "reversed" tail
(define (reversel lis)
  (if (empty? lis)
      lis
      (append (reversel (cdr lis)) (list (car lis)))))

; review of how filter works
(define (islessthan5 a)
  (< a 5))

; our own implementation of filter
; func needs to be a function that returns true or false and takes in a single param
; base case ... empty lis ===> return emtpy list
; recursive step ... nested if based on func
(define (myfilter func lis)
  (if (empty? lis) lis
      (if (func (car lis))
          (cons (car lis)
                (myfilter func (cdr lis)))
          (myfilter func (cdr lis)))))

; base case - i==0 
; recursive step (geti (cdr lis) (- i 1))
(define (geti lis i)
  (cond
    ((= i (length lis)) (print "error, indexoutofboundsexception") #f)
    ((= i 0) (car lis))
    (else
      (geti (cdr lis) (- i 1)))))

; returns the index of the first occurrence of val in the list
; returns -1 if not found
(define (findv lis val)
  (findvHelper lis val 0))

; recursive helper function for findv
;  lis - the list we are searching
;  val - the value we are searching for
;  i - where we are starting from (or thinking recursively, how far we have made it so far)
; base case 1 - i==len(lis) means we didn't find it, so return -1
; base case 2 - (car lis)==val means we found it!, so return i
; recursive step - (findvHelper (cdr lis) val (+ i 1))
(define (findvHelper lis val i)
  (cond
    ((empty? lis) -1)
    ((= (car lis) val) i)
    (else (findvHelper (cdr lis) val (+ i 1)))))

; returns a list of the elements that were at the even indices in the original list
; (evenPositionsOnly '(1 2 3 4 5)) ==> '(1 3 5)
(define (evenPositionsOnly lis)
  (evenPositionsOnlyH lis 0))

; base case - empty list ... return empty list
(define (evenPositionsOnlyH lis i)
  (cond
    ((empty? lis) '())
    ((even? i) (cons (car lis) (evenPositionsOnlyH (cdr lis) (+ i 1))))
    (else (evenPositionsOnlyH (cdr lis) (+ i 1)))))

; reminder of how filter works
;  applies a function that takes in a single parameter to each element in the list
;  if the function returns true, that element is kept ... if false, the element is discarded
(define (evenVals lis)
  (filter even? lis))

; doesn't work with duplicates
; but here is how you use filter to get the even positions
; you have to search for the element and then see if the index was odd or even
(define (evenPos lis)
  (filter
     (lambda (element)
       (even? (findv lis element))) lis))

; sort (the really inefficient way)
;  base case ... list is empty
;  two recursive steps ... if first item is the smallest item then just cons it onto the sorted tail of the list
;  if it's not the smallest item then just return the sorted entire list but with the first item moved to the end
(define (sortL lis)
  (cond
    ((empty? lis) lis)
    ((= (car lis) (apply min lis)) (cons (car lis) (sortL (cdr lis))))
    (else
     (sortL (append (cdr lis) (list (car lis)))))))

; returns how many times element appears in the list
(define (countElement lis element)
  (cond
    ((empty? lis) 0)
    ((= (car lis) element) (+ 1 (countElement (cdr lis) element)))
    (else (countElement (cdr lis) element))))


(sortL '(5 4 3 2 1))