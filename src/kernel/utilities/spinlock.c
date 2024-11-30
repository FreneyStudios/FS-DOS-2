#include <spinlock.h>
#include <system.h>

void spinlockAcquire(Spinlock *lock) {
  while (atomic_flag_test_and_set_explicit(lock, memory_order_acquire))
    handControl();
}

void spinlockRelease(Spinlock *lock) {
  atomic_flag_clear_explicit(lock, memory_order_release);
}

// Cnt spinlock is basically just a counter that increases for every read
// operation. When something has to modify, it waits for it to become 0 and
// makes it -1, not permitting any reads. Useful for linked lists..

void spinlockCntReadAcquire(SpinlockCnt *lock) {
  while (lock->cnt < 0)
    handControl();
  lock->cnt++;
}

void spinlockCntReadRelease(SpinlockCnt *lock) {
  if (lock->cnt < 0) {
    debugf("[spinlock] Something very bad is going on...\n");
    panic();
  }

  lock->cnt--;
}

void spinlockCntWriteAcquire(SpinlockCnt *lock) {
  while (lock->cnt != 0)
    handControl();
  lock->cnt = -1;
}

void spinlockCntWriteRelease(SpinlockCnt *lock) {
  if (lock->cnt != -1) {
    debugf("[spinlock] Something very bad is going on...\n");
    panic();
  }
  lock->cnt = 0;
}

void semaphoreWait(Semaphore *sem) {
  while (sem->cnt < 1)
    handControl();

  spinlockAcquire(&sem->LOCK);
  sem->cnt--;
  spinlockRelease(&sem->LOCK);
}

void semaphorePost(Semaphore *sem) {
  spinlockAcquire(&sem->LOCK);
  sem->cnt++;
  spinlockRelease(&sem->LOCK);
}
