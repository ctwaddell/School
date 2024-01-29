SHELL	:=	sh

#Only have one file to be compiled, just needs to execute on tests

setup:
	cp src/test_driver.c .
	cp src/linked_list_sol.h .

all:
	gcc test_driver.c -o test

clean:
	rm final_* 
	rm tests/Clear/output_Clear*
	rm tests/CountIf/output_CountIf*
	rm tests/Delete/output_Delete*
	rm tests/IsEmpty/output_IsEmpty*
	rm tests/PopBack/output_PopBack*
	rm tests/PopFront/output_PopFront*
	rm tests/PushBack/output_PushBack*
	rm tests/PushFront/output_PushFront*
	rm tests/RemoveDuplicates/output_RemoveDuplicates*
	rm tests/Size/output_Size*
	rm tests/Driver/output_Driver*

alltests: Clear CountIf Delete IsEmpty PopBack PopFront PushBack PushFront RemoveDuplicates Size Driver


Clear:
	./test < tests/Clear/input_Clear_1 > tests/Clear/output_Clear_1
	./test < tests/Clear/input_Clear_2 > tests/Clear/output_Clear_2
	./test < tests/Clear/input_Clear_3 > tests/Clear/output_Clear_3
	./test < tests/Clear/input_Clear_4 > tests/Clear/output_Clear_4
	cat tests/Clear/output_Clear_* >> final_Clear_output

CountIf:
	./test < tests/CountIf/input_CountIf_1 > tests/CountIf/output_CountIf_1
	./test < tests/CountIf/input_CountIf_2 > tests/CountIf/output_CountIf_2
	./test < tests/CountIf/input_CountIf_3 > tests/CountIf/output_CountIf_3
	./test < tests/CountIf/input_CountIf_4 > tests/CountIf/output_CountIf_4
	cat tests/CountIf/output_CountIf_* >> final_CountIf_output

Delete:
	./test < tests/Delete/input_Delete_1 > tests/Delete/output_Delete_1
	./test < tests/Delete/input_Delete_2 > tests/Delete/output_Delete_2
	./test < tests/Delete/input_Delete_3 > tests/Delete/output_Delete_3
	./test < tests/Delete/input_Delete_4 > tests/Delete/output_Delete_4
	cat tests/Delete/output_Delete_* >> final_Delete_output

IsEmpty:
	./test < tests/IsEmpty/input_IsEmpty_1 > tests/IsEmpty/output_IsEmpty_1
	./test < tests/IsEmpty/input_IsEmpty_2 > tests/IsEmpty/output_IsEmpty_2
	./test < tests/IsEmpty/input_IsEmpty_3 > tests/IsEmpty/output_IsEmpty_3
	./test < tests/IsEmpty/input_IsEmpty_4 > tests/IsEmpty/output_IsEmpty_4
	cat tests/IsEmpty/output_IsEmpty_* >> final_IsEmpty_output

PopBack:
	./test < tests/PopBack/input_PopBack_1 > tests/PopBack/output_PopBack_1
	./test < tests/PopBack/input_PopBack_2 > tests/PopBack/output_PopBack_2
	./test < tests/PopBack/input_PopBack_3 > tests/PopBack/output_PopBack_3
	./test < tests/PopBack/input_PopBack_4 > tests/PopBack/output_PopBack_4
	cat tests/PopBack/output_PopBack_* >> final_PopBack_output

PopFront:
	./test < tests/PopFront/input_PopFront_1 > tests/PopFront/output_PopFront_1
	./test < tests/PopFront/input_PopFront_2 > tests/PopFront/output_PopFront_2
	./test < tests/PopFront/input_PopFront_3 > tests/PopFront/output_PopFront_3
	./test < tests/PopFront/input_PopFront_4 > tests/PopFront/output_PopFront_4
	cat tests/PopFront/output_PopFront_* >> final_PopFront_output

PushBack:
	./test < tests/PushBack/input_PushBack_1 > tests/PushBack/output_PushBack_1
	./test < tests/PushBack/input_PushBack_2 > tests/PushBack/output_PushBack_2
	./test < tests/PushBack/input_PushBack_3 > tests/PushBack/output_PushBack_3
	./test < tests/PushBack/input_PushBack_4 > tests/PushBack/output_PushBack_4
	cat tests/PushBack/output_PushBack_* >> final_PushBack_output

PushFront:
	./test < tests/PushFront/input_PushFront_1 > tests/PushFront/output_PushFront_1
	./test < tests/PushFront/input_PushFront_2 > tests/PushFront/output_PushFront_2
	./test < tests/PushFront/input_PushFront_3 > tests/PushFront/output_PushFront_3
	./test < tests/PushFront/input_PushFront_4 > tests/PushFront/output_PushFront_4
	cat tests/PushFront/output_PushFront_* >> final_PushFront_output

RemoveDuplicates:
	./test < tests/RemoveDuplicates/input_RemoveDuplicates_1 > tests/RemoveDuplicates/output_RemoveDuplicates_1
	./test < tests/RemoveDuplicates/input_RemoveDuplicates_2 > tests/RemoveDuplicates/output_RemoveDuplicates_2
	./test < tests/RemoveDuplicates/input_RemoveDuplicates_3 > tests/RemoveDuplicates/output_RemoveDuplicates_3
	./test < tests/RemoveDuplicates/input_RemoveDuplicates_4 > tests/RemoveDuplicates/output_RemoveDuplicates_4
	cat tests/RemoveDuplicates/output_RemoveDuplicates_* >> final_RemoveDuplicates_output

Size:
	./test < tests/Size/input_Size_1 > tests/Size/output_Size_1
	./test < tests/Size/input_Size_2 > tests/Size/output_Size_2
	./test < tests/Size/input_Size_3 > tests/Size/output_Size_3
	./test < tests/Size/input_Size_4 > tests/Size/output_Size_4
	cat tests/Size/output_Size_* >> final_Size_output

Driver:
	./test < tests/Driver/input_Driver_1 > tests/Driver/output_Driver_1
	./test < tests/Driver/input_Driver_2 > tests/Driver/output_Driver_2
	cat tests/Driver/output_Driver_* >> final_Driver_output

