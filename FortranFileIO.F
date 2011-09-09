      subroutine FileOpen( unitNumber, filePath )
        integer unitNumber
        character*(*) filePath
        open(unit = unitNumber, file = filePath, status = 'old')
      end subroutine

      subroutine FileClose( unitNumber )
        integer unitNumber
        close( unitNumber )
      end subroutine

      subroutine FileReadLine( unitNumber, line )
        integer unitNumber
        character*(*) line
        read(unitNumber, '(A)') line
      end subroutine

      subroutine StringReadString( inputString, outputString )
        character*(*) inputString
        character*(*) outputString
        read(inputString, *) outputString
      end subroutine

      subroutine StringReadInteger( inputString, targetInt )
        character*(*) inputString
        integer targetInt
        read(inputString, *) targetInt
      end subroutine

      subroutine StringReadDouble( inputString, targetDouble )
        character*(*) inputString
        double precision targetDouble
        read(inputString, *) targetDouble
      end subroutine
