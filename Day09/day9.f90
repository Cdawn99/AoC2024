module utils
    implicit none

contains

    function read_entire_file(filepath, stat) result(content)
        character(*), intent(in) :: filepath
        integer, intent(out) :: stat
        character(:), allocatable :: content

        character(512) :: msg
        integer :: io, ios
        integer :: filesize

        stat = 0

        inquire(file=filepath, size=filesize)
        if (filesize == -1) then
            print '(A)', 'Cannot determine filesize'
            stat = -1
            return
        end if
        filesize = filesize - 1

        open(newunit=io, iostat=ios, iomsg=msg, file=filepath, status='old', action='read')
        if (ios /= 0) then
            print '(A)', trim(msg)
            stat = ios
            return
        end if

        allocate(character(filesize) :: content)
        read(io,*) content

        close(io)
    end function read_entire_file
end module utils
