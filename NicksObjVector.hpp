#ifndef NICKS_VECTOR_H
#define NICKS_VECTOR_H

#include <stdexcept>
#include "Logger.hpp"
#include <type_traits>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>


template <typename T> 
class NicksObjVector {

private:
    // state
    T *A;
    int max;
    int n;
    bool is_pointer; // tracks if the values stored are pointers


    // boost serialisation
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        using boost::serialization::make_nvp;

        ar & make_nvp("n", n);
        ar & make_nvp("max", max);
        ar & make_nvp("is_pointer",is_pointer);
                
        if (Archive::is_loading::value) {
            //Logger::all[0]->log_info("making vector size: "+std::to_string(max));
            A = new T[max];
        }
                
        for (int i=0; i<n; i++){
            ar & make_nvp("A", A[i]);
        }
    }

public:
    // default constructor
    NicksObjVector(){
        n = 0;
        max = 0; // no array yet
        A = nullptr; // no array set yet

        if (std::is_pointer<T>::value) {
            is_pointer = true;
        } else {
            is_pointer = false;
        }
    }

    NicksObjVector(std::initializer_list<T> list) : NicksObjVector() {

        for (const T* val = list.begin(); val != list.end(); ++val){
            this->push( *val );
        }

    }

    // methods
    void push(T data){ // add element to the end of vector
        if (n == max){
            max = (max+1)*2;
            T* temp = new T[max];
            for (int i=0; i<n; i++){
                temp[i] = A[i];
            }
            delete[] A;
            A = temp;
        }
        A[n] = data;
        n++;
    } 

    void push(T data, int index){ // push, but at a given index rather than the end. Won't overwrite data at the index, will shift everything first
        if (n==max) {
            T* temp = new T[(max+1)*2];
            for (int i=0, j=0; i<n; i++, j++){
                if (i == index){
                    temp[j] = data;
                    j++;
                    temp[j] = A[i];
                } else {
                    temp[j] = A[i];
                }
            }
            delete[] A;
            A = temp;
        } else {
            T temp[2] = {};

            temp[0] = A[index];
            A[index] = data;

            for (int i=index+1; i<n; i=i+2){
                temp[1] = A[i];
                A[i] = temp[0];

                if (i < n-1){ // only save 2nd overwritten val if its not the last element
                    temp[0] = A[i+1];
                }

                A[i+1] = temp[1];
            }
        }

        max = (max+1)*2;
        n++;
    }

    T pop(int index){ // remove element by index and return it

        if (-1 < index && index < n){
            if (index == n-1){
                n--;
                return A[index];
            } else if (index < n-1){
                T returnVal = A[index];

                int delta = n-index-1;
                T temp[delta];
                for (int i=index+1, j=0; i<n; i++,j++){
                    temp[j] = A[i];
                }
                for (int i=index, j=0; j<delta; i++,j++){
                    A[i] = temp[j];
                }
                n--;
                return returnVal;
            }
        }

        throw "Out of range";
    } 
    int size() { return n; }; // returns the number of the elements in the vector


    int indexOf(T data){ // search the vector and return the first index of the param. if not found, return -1.
        int index = -1;
        for (int i=0; i<n; i++){
            if (A[i] == data){
                index = i;
                break;
            }
        }
        return index;    
    }

    /**
     * return pointer to element in place
     */
    T* get(int index) { // return pointer to element at index
        if (index > -1 && index < n){
            return &A[index]; 
        } else {
            throw std::invalid_argument("index out of bounds");
        }
    }

    T* copy(){ // return a pointer to an array copy of the vector 
        T *array = new T[n];
        for (int i=0; i<n; i++){
            array[i] = A[i];
        }

        return array;
    }

    NicksObjVector<T>* ptr(){
        return this;
    }

    /**
     * return element by value (a copy)
     */
    T e(int index) {
        if (index > -1 && index < n){
            return A[index]; 
        } else {
            throw std::invalid_argument("index out of bounds");
        }
        
    }

    T operator[](int index) {
        return e(index);
    }

    /**
     * If the values stored are pointers, runs delete on all values
     */
    void deleteAll() {
        if (is_pointer) {
            for (int i=0; i<n; i++){
                delete A[i];
            }
        }
    }

    // destructor
    ~NicksObjVector(){
        delete[] A;
    }

};

#endif