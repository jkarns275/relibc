use core::ptr;

use errno::ENOMEM;
use platform;
use platform::types::*;

static mut BRK: *mut c_void = ptr::null_mut();

#[no_mangle]
pub unsafe extern "C" fn brk(addr: *mut c_void) -> c_int {
    BRK = platform::brk(addr);

    if BRK < addr {
        platform::errno = ENOMEM;
        return -1;
    }

    0
}

#[no_mangle]
pub unsafe extern "C" fn sbrk(incr: intptr_t) -> *mut c_void {
    if BRK == ptr::null_mut() {
        BRK = platform::brk(ptr::null_mut());
    }

    let old_brk = BRK;

    if incr != 0 {
        let addr = old_brk.offset(incr);

        BRK = platform::brk(addr);

        if BRK < addr {
            platform::errno = ENOMEM;
            return -1isize as *mut c_void;
        }
    }

    old_brk as *mut c_void
}
