/*
 * Learn BSP is a sample source code to see how a Half-Life level file
 * can be used in your 3D application
 * Copyright (C) 2009  Wouter Saaltink

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _INDEXARRAY_H
#define	_INDEXARRAY_H

template<const int elem_size>
class IndexArray {
public:
#define CHUNK   (4096)
    IndexArray() {
        size = CHUNK*elem_size;
        data = new float[size];
        count = 0;
    }

    ~IndexArray() {
        if(data) {
            delete []data;
            data = 0;
        }
    }

    void add(float* src) {
        if(count >= size/elem_size) {
            //resize
            int s = size;
            size += CHUNK*elem_size;
            float* n = new float[size];
            for(int i = 0; i < s; i++) {
                n[i] = data[i];
            }
            delete data;
            data = n;
        }

        float* dst = data + count*elem_size;
        for(int i = 0; i < elem_size; i++) {
            *dst++ = *src++;
        }
        count++;
    }

    operator float*(void) const { return data; }
    const float* operator[](int i) const { return data + i*elem_size; }

    int current() const { return count; }

private:
    int size;
    int count;
    float* data;
};

#endif	/* _INDEXARRAY_H */

