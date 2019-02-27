package Pool
import(
	"fmt"
)

type Worker struct{
	pool * Pool
	task chan f
}

func (w *Worker)run(){
	go func(){
		for f := range w.task{
			if f == nil{
				atomic.AddInt32(&w.pool.running,-1)
				return
			}
			f()
			w.pool.putWorker(w)
		}
	}()
}

func (w *Worker) stop(){
	w.sendTask(nil)
}

func (w *Worker)sendTask(task f){
	w.task <- task
}

func (p* Pool)putWorker(worker *Worker){
	p.lock.Lock()
	p.workers = append(p.workers,worker)
	p.lock.Unlock()
	p.freeSignal <- sig{}
}

func (p *Pool)ReSize(size int){
	if size < p.Cap(){
		diff := p.Cap() - size
		for i := 0;i<diff;i++{
			p.getWorker().stop()
		}
	}else if size == p.Cap(){
		return
	}
	atomic.StoreInt32(&p.capacity,int32(size))
}