#Nginx Source Code Analysis

The respository contains the documents for analysis of nginx source code.
The following concepts are explained in this file.

#Repository Structure

__/nginx__
     /Memory Management       ---  Memory pool and related operations
     /Buffer Management       ---  Structure of Buffer,types of buffer and buffer operations
     /Data Structures in nginx    --- Explaination of structure and operations on various data structures
          /Arrays
          /Lists
          /Queues
          /RB Tree
          /Radix Tree
          /Hash Table
     /Chain of Buffers        --- Chain implementation of Buffers
     /Test Scripts            --- This directory contains C program samples showing
                                      - Implementaion of data structures
                                      - Implementaion of Memory Pools
                                      - Buffer Implementation