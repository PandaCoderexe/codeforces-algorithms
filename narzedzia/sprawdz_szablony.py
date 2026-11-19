"""Porównaj struktury z naiwną tablicą i utrwalonymi wersjami."""
import subprocess


PRELUDE = '''
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
'''


def run_template_checks(catalog, root, compiler, build_dir):
    checks = []
    for record in catalog['records']:
        if record['source'] not in {'tree/segTree.cc', 'tree/fenqick.cc', 'tree/pst.cc', '648/sorting/648B.cc'}:
            continue
        for example in record['examples']:
            path = root / example['destination']
            if record['source'] == '648/sorting/648B.cc':
                program = '''
struct Item {
    int value,id;
    bool operator<=(const Item& other) const {return value<=other.value;}
};
int main() {
    mt19937 rng(526);
    int checks=0;
    for(int n=0;n<=60;n++) for(int trial=0;trial<10;trial++) {
        vector<Item>a;
        for(int i=0;i<n;i++) a.push_back({(int)(rng()%11)-5,i});
        auto expected=a;
        stable_sort(expected.begin(),expected.end(),[](Item x,Item y){return x.value<y.value;});
        merge(a,0,n-1);
        for(int i=0;i<n;i++) if(a[i].value!=expected[i].value || a[i].id!=expected[i].id) return 1;
        checks++;
    }
    cout<<checks;
}
'''
            elif record['source'] == 'tree/pst.cc':
                program = '''
int main() {
    vector<int> a={3,1,4,1,5,9,2,6,5};
    PST pst(16);
    vector<int> roots={0};
    for (int x:a) roots.push_back(pst.update(roots.back(),1,10,x,1));
    int checks=0;
    for (int l=0;l<(int)a.size();l++) for (int r=l+1;r<=(int)a.size();r++) {
        vector<int> b(a.begin()+l,a.begin()+r);
        sort(b.begin(),b.end());
        for (int low=1;low<=10;low++) for (int high=low;high<=10;high++) {
            int expected=0;
            for (int x:b) expected+=(low<=x && x<=high);
            if (pst.queryDiffRange(roots[l],roots[r],1,10,low,high)!=expected) return 1;
            checks++;
        }
        for (int k=1;k<=(int)b.size();k++) {
            if (pst.queryPoint(roots[l],roots[r],1,10,k)!=b[k-1]) return 2;
            checks++;
        }
    }
    cout<<checks;
}
'''
            elif record['source'] == 'tree/fenqick.cc':
                program = '''
int main() {
    mt19937 rng(8123);
    int checks=0;
    for(int n=1;n<=19;n++) {
        vector<long long>a(n+1);
        for(int i=1;i<=n;i++) a[i]=(int)(rng()%21)-10;
        Fenwick2 tree(n,a);
        for(int step=0;step<80;step++) {
            for(int r=0;r<=n;r++) {
                long long expected=0;
                for(int i=1;i<=r;i++) expected+=a[i];
                if(tree.sum(r)!=expected) return 1;
                checks++;
            }
            int pos=1+rng()%n,delta=(int)(rng()%21)-10;
            tree.add(pos,delta);
            a[pos]+=delta;
        }
    }
    cout<<checks;
}
'''
            else:
                filename = path.stem
                if filename == 'dodawanie_punktowe_i_suma':
                    struct = 'SegTree_PointRange'
                    update = 'tree.update(l,delta); a[l]+=delta;'
                    query = 'tree.query(ql,qr)'
                elif filename == 'dodawanie_na_przedziale_i_suma':
                    struct = 'SegTree_RangeRange'
                    update = 'tree.update(l,r,delta); for(int i=l;i<=r;i++) a[i]+=delta;'
                    query = 'tree.rangeQuery(ql,qr)'
                else:
                    struct = 'SegTree_RangePoint'
                    update = 'tree.update(l,r,delta); for(int i=l;i<=r;i++) a[i]+=delta;'
                    query = 'tree.query(ql)'
                point = struct == 'SegTree_RangePoint'
                program = '''
int main() {
    mt19937 rng(418);
    int checks=0;
    for(int n=1;n<=19;n++) {
        vector<long long>a(n);
        for(auto &x:a) x=(int)(rng()%21)-10;
        STRUCT tree(n,a);
        for(int step=0;step<80;step++) {
            for(int ql=0;ql<n;ql++) for(int qr=ql;qr<(POINT ? ql+1 : n);qr++) {
                long long expected=0;
                for(int i=ql;i<=qr;i++) expected+=a[i];
                if(POINT) expected=a[ql];
                if(QUERY!=expected) return 1;
                checks++;
            }
            int l=rng()%n,r=rng()%n;
            if(l>r) swap(l,r);
            int delta=(int)(rng()%21)-10;
            UPDATE
        }
    }
    cout<<checks;
}
'''.replace('STRUCT', struct).replace('POINT', 'true' if point else 'false').replace('QUERY', query).replace('UPDATE', update)
            harness = build_dir / (path.stem + '_test.cc')
            binary = build_dir / (path.stem + '_test')
            harness.write_text(PRELUDE + '\n#include "' + str(path) + '"\n' + program, encoding='utf-8')
            command = [compiler, '-std=c++20', '-O1', '-fsanitize=undefined',
                       '-fno-sanitize-recover=all', str(harness), '-o', str(binary)]
            result = subprocess.run(command, capture_output=True, text=True, timeout=60)
            item = {'name': example['title'], 'source': record['source'], 'file': example['destination'],
                    'cases': 0, 'status': 'failed'}
            if result.returncode:
                item['details'] = result.stderr[-3000:]
            else:
                result = subprocess.run([str(binary)], capture_output=True, text=True, timeout=10)
                if result.returncode == 0:
                    item.update(status='passed', cases=int(result.stdout), details='Porównano z naiwną tablicą lub posortowanym wycinkiem. UBSan aktywny.')
                else:
                    item['details'] = 'Niezgodny wynik struktury. ' + result.stderr[-1500:]
            checks.append(item)
    return checks
