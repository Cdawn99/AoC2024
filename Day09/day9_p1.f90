program day9
    use utils
    implicit none

    character(32) :: program_name
    character(32) :: filepath
    integer :: rstat

    character(:), allocatable :: disk_map_str
    integer :: i, n
    integer (kind=8) :: sum

    integer, allocatable :: disk_map(:)
    integer :: j, idx, id
    integer, allocatable :: decompressed_disk_map(:)
    integer :: temp

    call get_command_argument(0, program_name)
    if (command_argument_count() /= 1) then
        print '(A,A,A)', 'Usage: ', trim(program_name), ' <disk_map.txt>'
        stop
    end if

    call get_command_argument(1, filepath)
    disk_map_str = read_entire_file(filepath, rstat)
    if (rstat /= 0) then
        stop
    end if

    allocate(disk_map(len(disk_map_str)))
    sum = 0
    do i = 1, len(disk_map_str)
        n = iachar(disk_map_str(i:i)) - iachar('0')
        disk_map(i) = n
        sum = sum + n
    end do
    deallocate(disk_map_str)

    allocate(decompressed_disk_map(sum))

    idx = 1
    id = 0
    do i = 1, size(disk_map)
        do j = 1, disk_map(i)
            if (mod(i, 2) /= 0) then
                decompressed_disk_map(idx) = id
            else
                decompressed_disk_map(idx) = -1
            end if
            idx = idx + 1
        end do
        if (mod(i, 2) /= 0) then
            id = id + 1
        end if
    end do
    deallocate(disk_map)

    i = 1
    j = size(decompressed_disk_map)
    do
        do
            if (decompressed_disk_map(i) /= -1) then
                i = i + 1
            else
                exit
            end if
        end do
        do
            if (decompressed_disk_map(j) == -1) then
                j = j - 1
            else
                exit
            end if
        end do
        if (i > j) then
            exit
        end if
        temp = decompressed_disk_map(i)
        decompressed_disk_map(i) = decompressed_disk_map(j)
        decompressed_disk_map(j) = temp
    end do

    sum = 0
    i = 0
    do
        sum = sum + i * decompressed_disk_map(i + 1)
        i = i + 1
        if (decompressed_disk_map(i + 1) == -1) then
            exit
        end if
    end do

    print *, sum

    deallocate(decompressed_disk_map)
end program day9
