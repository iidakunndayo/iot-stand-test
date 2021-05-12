NewMultiple: NewBoard/MultipleControl/test.cpp
	g++ NewBoard/MultipleControl/test.cpp -Wall -o NewBoard/MultipleControl/test.out -lwiringPi

NewSingle: NewBoard/SingleControl/test.cpp
	g++ NewBoard/SingleControl/test.cpp -Wall -o NewBoard/SingleControl/test.out -lwiringPi

OldMultiple: OldBoard/MultipleControl/test.cpp
	g++ OldBoard/MultipleControl/test.cpp -Wall -o OldBoard/MultipleControl/test.out -lwiringPi

OldSingle: OldBoard/SingleControl/test.cpp
	g++ OldBoard/SingleControl/test.cpp -Wall -o OldBoard/SingleControl/test.out -lwiringPi

clean: 
	rm NewBoard/MultipleControl/test.out
	rm NewBoard/SingleControl/test.out
	rm OldBoard/MultipleControl/test.out
	rm OldBoard/SingleControl/test.out