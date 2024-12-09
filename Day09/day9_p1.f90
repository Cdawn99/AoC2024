program day9
    use utils
    implicit none

    character(32) :: program_name
    character(32) :: filepath
    character(:), allocatable :: disk_map
    integer :: rstat

    call get_command_argument(0, program_name)
    if (command_argument_count() /= 1) then
        print '(A,A,A)', 'Usage: ', trim(program_name), ' <disk_map.txt>'
        stop
    end if

    call get_command_argument(1, filepath)
    disk_map = read_entire_file(filepath, rstat)
    if (rstat /= 0) then
        stop
    end if

    print '(A)', disk_map

    deallocate(disk_map)
end program day9
