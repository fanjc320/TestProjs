package Pool
import(
	"fmt"
)

type sig struct{}

//Pool accept the tasks from client,it limits the total
// of goroutines to a given number by recycling goroutines.
type Pool struct{
	capacity int32
	running int32

	//freeSignal is used to notice pool there are available
	// workers which can be sent to work.
	freeSignal chan sig
	//workers is a slice that store the available workers.
	workers []* Worker

	//release is used to notice the pool to closed itself.
	release cha sig
	
	//lock for synchronous operation
	lock sync.Mutex

	once sync.Once
}

//Pool是一个通用的协程池，支持不同类型的任务，亦即每一个任务绑定一个函数提交到池中，批量执行不同类型任务，是一种广义的协程池；本项目中还实现了另一种协程池 — 批量执行同类任务的协程池PoolWithFunc，每一个PoolWithFunc只会绑定一个任务函数pf，这种Pool适用于大批量相同任务的场景，因为每个Pool只绑定一个任务函数，因此PoolWithFunc相较于Pool会更加节省内存，但通用性就不如前者了，为了让大家更好地理解协程池的原理，这里我们用通用的Pool来分析。
//capacity是该Pool的容量，也就是开启worker数量的上限，每一个worker绑定一个goroutine；running是当前正在执行任务的worker数量；freeSignal是一个信号，因为Pool开启的worker数量有上限，因此当全部worker都在执行任务的时候，新进来的请求就需要阻塞等待，那当执行完任务的worker被放回Pool之时，如何通知阻塞的请求绑定一个空闲的worker运行呢？freeSignal就是来做这个事情的；workers是一个slice，用来存放空闲worker，请求进入Pool之后会首先检查workers中是否有空闲worker，若有则取出绑定任务执行，否则判断当前运行的worker是否已经达到容量上限，是—阻塞等待，否—新开一个worker执行任务；release是当关闭该Pool支持通知所有worker退出运行以防goroutine泄露；lock是一个锁，用以支持Pool的同步操作；once用在确保Pool关闭操作只会执行一次。

//提交任务到Pool
func (p *Pool) Submit(task f)error{
	if len(p.release) >0 {
		return ErrPoolClosed
	}
	w := p.getWorker()
	w.sendTask(task)
	return nil
}

//获取可用worker(核心)

func (p *Pool)getWorker() *Worker{
	var w *Worker
	//标志，表示当前运行的workers数量是否已达容量上限
	waiting := false
	//涉及从workers队列取可用worker,需要加锁
	p.lock.Lock()
	workers := p.workers
	n := len(workers) - 1
	//当前worker队列为空（无空闲worker)
	if n < 0 {
		//运行worker数目已达到该Pool的容量上限，置等待标志
		if p.running >= p.capacity {
			waiting = true
		}else{
			p.running++
		}
	}else{
		<-p.freeSignal //!!!!!!
		w = workers[n]
		workers[n] = nil
		p.workers = workers[:n]//!!!!!
	}
	//判断是否有worker可用结束，解锁
	p.lock.Unlock()

	if waiting {
		//阻塞等待直到有空闲worker!!!!!!!
		<-p.freeSignal
		p.lock.Lock()
		workers = p.workers

	}
}
